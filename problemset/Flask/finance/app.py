import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    data = db.execute(
        "SELECT symbol, name, sum(shares) AS shares FROM portfolio JOIN users ON portfolio.user_id = users.id WHERE user_id = ? GROUP BY symbol;",
        session["user_id"],
    )
    cashdata = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cashdata[0]["cash"]
    fulltotal = 0
    for row in data:
        symbol = lookup(row["symbol"])
        currentprice = float(symbol["price"])
        total = row["shares"] * currentprice
        row.update({"price": currentprice})
        row.update({"total": total})
        fulltotal = fulltotal + total

    return render_template("index.html", data=data, fulltotal=fulltotal, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        cashquery = db.execute(
            "SELECT cash FROM users Where id = ?", session["user_id"]
        )
        cash = cashquery[0]["cash"]
        symbol = lookup(request.form.get("symbol"))

        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Must enter whole number", 400)

        if not request.form.get("symbol"):
            return apology("Must enter a symbol", 403)
        elif not symbol:
            return apology("Invalid symbol", 400)
        elif not request.form.get("shares"):
            return apology("Must enter a share", 403)
        elif int(request.form.get("shares")) < 1:
            return apology(" Must enter a valid share", 400)
        elif cash - (int(request.form.get("shares")) * float(symbol["price"])) < 0:
            return apology("Not enough balance", 403)
        else:
            time = datetime.now().strftime("%d/%m/%y %H:%M:%S")
            type = "Bought"
            db.execute(
                "INSERT INTO buy (user_id, name, symbol, shares, type, price, time) VALUES (?, ?, ?, ?, ?, ?, ?)",
                session["user_id"],
                symbol["name"],
                request.form.get("symbol"),
                int(request.form.get("shares")),
                type,
                float(symbol["price"]),
                time,
            )
            cash = cash - (int(request.form.get("shares")) * float(symbol["price"]))
            db.execute(
                "UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"]
            )
            i = 0
            for i in range(int(request.form.get("shares"))):
                db.execute(
                    "INSERT INTO portfolio (user_id, name, symbol, shares, price, time) VALUES (?, ?, ?, ?, ?, ?)",
                    session["user_id"],
                    symbol["name"],
                    request.form.get("symbol"),
                    1,
                    float(symbol["price"]),
                    time,
                )
        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute(
        "SELECT symbol, shares, type, price, time FROM buy WHERE user_id = ?",
        session["user_id"],
    )

    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
       
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        share = lookup(request.form.get("symbol"))

        if not request.form.get("symbol"):
            return apology("Must enter a symbol", 400)
        elif not share:
            return apology("Invalid symbol", 400)

        return render_template(
            "quoted.html",
            name=share["name"],
            symbol=share["symbol"],
            price=share["price"],
        )
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        usersdict = db.execute("SELECT username FROM users")
        user = []
        for row in usersdict:
            user.append(row["username"])

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        elif request.form.get("username") in user:
            return apology("Username alredy taken", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password confirmation incorrect", 400)

        else:
            db.execute(
                "INSERT INTO users (username, hash) VALUES(?, ?)",
                request.form.get("username"),
                generate_password_hash(request.form.get("password")),
            )

            return redirect("/login")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    data = db.execute(
        "SELECT symbol, SUM(shares) AS shares FROM portfolio JOIN users ON portfolio.user_id = users.id WHERE user_id = ? GROUP BY symbol;",
        session["user_id"],
    )
    symbols = []
    stock = {}
    for row in data:
        symbols.append(row["symbol"])
        stock.update({row["symbol"]: row["shares"]})
    print(stock)

    if request.method == "POST":
        selectedsymbol = request.form.get("symbol")
        selectedshares = request.form.get("shares")

        # Ensure symbol is provided and a valid number of share are selected
        if selectedsymbol not in symbols:
            return apology("must provide a symbol", 403)
        elif selectedshares == "":
            return apology("must provide a valid share", 403)
        elif int(selectedshares) < 1:
            return apology("must provide a valid share", 403)
        elif int(selectedshares) > stock[selectedsymbol]:
            return apology("Not enough share", 400)

        # checking current price and updating the users total cash
        else:
            APIsymbol = lookup(selectedsymbol)
            currentprice = float(APIsymbol["price"])
            gain = currentprice * int(selectedshares)

            cashdata = db.execute(
                "SELECT cash FROM users WHERE id = ?", session["user_id"]
            )
            cash = cashdata[0]["cash"]

            totalcash = cash + gain
            # update cash
            db.execute(
                "UPDATE users SET cash = ? WHERE id = ?", totalcash, session["user_id"]
            )
            # update portfolio
            db.execute(
                "DELETE FROM portfolio WHERE user_id = ? AND symbol = ? LIMIT ?",
                session["user_id"],
                selectedsymbol,
                selectedshares,
            )
            # update buy table with sold items too
            time = datetime.now().strftime("%d/%m/%y %H:%M:%S")
            type = "Sold"
            db.execute(
                "INSERT INTO buy (user_id, name, symbol, shares, type, price, time) VALUES (?, ?, ?, ?, ?, ?, ?)",
                session["user_id"],
                APIsymbol["name"],
                selectedsymbol,
                int(selectedshares),
                type,
                currentprice,
                time,
            )
            return redirect("/")

    return render_template("sell.html", symbols=symbols)


@app.route("/money", methods=["GET", "POST"])
def money():
    """Add money to account"""
    if request.method == "POST":
        try:
            money = int(request.form.get("money"))
        except:
            return apology("Must enter whole number", 400)

        if not request.form.get("money"):
            return apology("Must enter a value", 403)
        elif int(request.form.get("money")) < 1:
            return apology("Min 1$", 400)
        else:
            cashdata = db.execute(
                "SELECT cash FROM users WHERE id = ?", session["user_id"]
            )
            cash = cashdata[0]["cash"]
            updatedcash = cash + int(request.form.get("money"))

            db.execute(
                "UPDATE users SET cash = ? WHERE id = ?",
                updatedcash,
                session["user_id"],
            )

        return redirect("/")
    return render_template("money.html")
