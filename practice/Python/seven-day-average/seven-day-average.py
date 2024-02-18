import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


#TO Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):

    new_cases = dict()
    previous_case = dict()

    for row in reader:
        state = row['state']
        cases = int(row['cases'])

        if state not in new_cases:
            new_cases[state] = []

        if len(new_cases[state]) > 14:
            new_cases[state].pop(0)



        if state in previous_case:
            new_case_today = cases - previous_case[state]
        else:
            new_case_today = cases

        new_cases[state].append(new_case_today)
        previous_case[state] = cases

    return new_cases

# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):

    for state in states:
        thiswwek = sum(new_cases[state][7:14]) / 7
        lastweek = sum(new_cases[state][0:7]) / 7
        

        try:
            percentage = ((thiswwek - lastweek) / lastweek) *100
        except ZeroDivisionError:
            print("Cannot divide by zero!")
            continue

        if thiswwek > lastweek:
            print(f"{state} had a 7-day average of {thiswwek: .2f} and a increase of {percentage: .2f}%")
        else:
            print(f"{state} had a 7-day average of {thiswwek: .2f} and a dencrease of {percentage: .2f}%")


main()
