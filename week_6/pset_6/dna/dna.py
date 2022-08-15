import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    databaseList = list()

    with open(sys.argv[1], "r") as database:
        reader = csv.DictReader(database)
        for line in reader:
            databaseList.append(line)

    # TODO: Read DNA sequence file into a variable
    dnaCounts = dict()

    with open(sys.argv[2], "r") as textfile:
        dnaSequence = textfile.read()

    # TODO: Find longest match of each STR in DNA sequence
    subsequences = list()
    dnaCount = dict()
    keys = databaseList[0].keys()
    keysLenght = len(keys)

    for key in keys:
        subsequences.append(key)
    subsequences.remove("name")

    for subsequence in subsequences:
        numCount = longest_match(dnaSequence, subsequence)
        dnaCount[subsequence] = numCount

    # TODO: Check database for matching profiles
    for person in databaseList:
        matches = 0
        for key, value in dnaCount.items():
            if int(person[key]) == value:
                matches += 1
        if matches == len(dnaCount):
            print(person['name'])
            exit(0)

    print("No match")


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
