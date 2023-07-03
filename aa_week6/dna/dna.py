import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: database.csv sequence.txt")
        sys.exit(1)

    csv_database = sys.argv[1]
    txt_sequence = sys.argv[2]
    # TODO: Read database file into a variable

    #this is a quick way to open a file
    with open(csv_database, "r") as csv_file:
        #DictReader returns the dictionary keys used as header of file
        db_reader = csv.DictReader(csv_file)
        #this converts it into a list
        db_list = list(db_reader)
    #print(db_list)
    #print(len(db_list))

    # TODO: Read DNA sequence file into a variable
    with open(txt_sequence, "r") as txt_file:
        seq_reader = txt_file.read()
    #print(seq_reader)

    # TODO: Find longest match of each STR in DNA sequence
    max = []

    for i in range(1, len(db_reader.fieldnames)):
        STR = db_reader.fieldnames[i]
        max.append(0)
        max[i - 1] = longest_match(seq_reader, STR)

    # TODO: Check database for matching profiles
    #loop through all the people
    for i in range(len(db_list)):
        matches = 0
        #loop through all the STRs
        for j in range(1, len(db_reader.fieldnames)):
            #if STR of the person matches the seq max we ++ matches
            if max[j - 1] == int(db_list[i][db_reader.fieldnames[j]]):
                matches += 1
            #if there are matches == to the amout of STRs (-1 because we eliminate the name in the header) print name and exit success
            if matches == (len(db_reader.fieldnames)) - 1:
                print(db_list[i]['name'])
                sys.exit(0)

    print("No Match")
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
        # max returns the highest number from the input
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()


#--------------------------------------------
    # we make a list of all the maxium STRs
    #max = []
    # we loop over the STRs in the header of the db_reader variable using firldnames which gives us the STR names/values
    # name,AGATC,AATG,TATC excluding the first value "names" because we dont care about them for now
    # when i increments we also append(0) to make room in the list for the next max STR
    #for i in range(1, len(db_reader.fieldnames)):
        #STR = db_reader.fieldnames[i]
        #max.append(0)

        #we look for the STR in the txt file. When we find a match we count how many times it repeats by adding the repeat_STR variable to the indexing of seq_reader
        #for j in range(len(seq_reader)):
            #count = 0
            #if seq_reader[j : j + len(STR)] == STR:
                #repeat_STR = 0
                #while seq_reader[j + repeat_STR : j + len(STR) + repeat_STR] == STR:
                    #count += 1
                    #repeat_STR += len(STR)
            # if higher than current count then replace (use - 1 because our i value is one higher than the index of the max [] list)
            #if count > max[i - 1]:
                #max[i - 1] = count
