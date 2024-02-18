# TODO
import cs50


def main():
    while True:
        owed = cs50.get_float("Change owed: ")
        if owed > 0:
            break

    count = 0
    # calcucalte 25
    quarters = husz(owed)
    count = count + quarters
    owed = owed - (0.25 * quarters)
    owed = round(owed, 2)
    # calcucalte 10
    dimes = tiz(owed)
    count = count + dimes
    owed = owed - (0.10 * dimes)
    owed = round(owed, 2)
    # calcucalte 5
    nickles = ot(owed)
    count = count + nickles
    owed = owed - (0.05 * nickles)
    owed = round(owed, 2)

    # calcucalte 1
    pennie = egy(owed)
    count = count + pennie
    owed = owed - (0.01 * pennie)
    owed = round(owed, 2)

    print(count)


# 25,10, 5, 1


def husz(cents):
    count = 0
    while cents >= 0.25:
        cents = cents - 0.25
        count += 1
    return count


def tiz(cents):
    count = 0
    while cents >= 0.10:
        cents = cents - 0.10
        count += 1
    return count


def ot(cents):
    count = 0
    while cents >= 0.05:
        cents = cents - 0.05
        count += 1
    return count


def egy(cents):
    count = 0
    while cents >= 0.01:
        cents = cents - 0.01
        count += 1
    return count


main()
