import csv
import sys


def main():
    # TODO: Check for command-line usage / 1st name of csv file / 2nd tx file
    # incorrect number of cla: print error

    if len(sys.argv) != 3:
        print("Usage: CSV file name + txt file name")
        sys.exit(1)

    csvf = sys.argv[1]
    txt = sys.argv[2]

    # TODO: Read database file into a variable >>>>> database = []
    database = []
    with open(csvf) as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)
    ##print(database[0])

    # TODO: Read DNA sequence file into a variable
    with open(txt) as f:
        dna_reader = csv.reader(f)
        for i in dna_reader:
            dna = i[0]
    ##print(dna)

    # TODO: Find longest match of each STR in DNA sequence

    matches = {}
    for i in database[0]:
        matches[i] = longest_match(dna, i)

    # TODO: Check database for matching profiles
    counter = 0

    for i in range(len(database)):  # hanyszor iteraljon
        counter = 0
        for j in database[0]:  # key iteralas
            if database[i][j].isnumeric():
                database_value = int(database[i][j])
                if database_value == matches[j]:
                    counter += 1
                    if counter == (len(matches) - 1):
                        print(database[i]["name"])
                        break
    if counter != (len(matches) - 1):
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
