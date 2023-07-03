def main():
    hashes = get_hashes()
    counter = 1
    spaceCounter = hashes

    while counter <= hashes:
        print(" " * (spaceCounter - 1), end="")
        print("#" * counter)
        counter += 1
        spaceCounter -= 1


def get_hashes():
    while True:
        try:
            hashes = int(input("Height: "))
            if hashes > 0 and hashes <= 8:
                return hashes
        except ValueError:
            print("Not a number")


main()