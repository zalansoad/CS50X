from cs50 import SQL

#Open database
db = SQL("sqlite:///roster.db")

rows = db.execute("Select house, head FROM students")
for row in rows:
    house = row['house']
    head = row['head']
    existing_record = db.execute("SELECT house FROM houses WHERE house = ?", house)
    if not existing_record:
        db.execute("INSERT INTO houses (house, head) VALUES (?, ?)", house, head)

rows2 = db.execute("Select student_name, head FROM students")
for row in rows2:
    student = row['student_name']
    db.execute("INSERT INTO students_only (student_name) VALUES (?)", student)

rows3 = db.execute("Select student_name, house FROM students")
for row in rows3:
    name = row['student_name']
    id = db.execute("SELECT id FROM students WHERE student_name = ?", name)
    value = id[0]["id"]

    chouse = row['house']
    hid = db.execute("SELECT id FROM houses WHERE house = ?", chouse)
    valueh = hid[0]["id"]

    db.execute("INSERT INTO assgnments (student_id, house_id) VALUES (?, ?)", value, valueh)






