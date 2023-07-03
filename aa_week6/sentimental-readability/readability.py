def main():
    input = get_input()
    words = get_words(input)
    sentences = get_sentences(input)
    letters = get_letters(input)

    CLindex = round(0.0588 * letters * 100 / words - 0.296 * sentences * 100 / words - 15.8)

    if CLindex < 1:
        print("Before Grade 1")
    elif CLindex >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {CLindex}")


def get_input():
    while True:
        try:
            text = input("Text: ")
            return text
        except ValueError:
            print("Not valid input")


def get_words(input):
    count = 1
    length = len(input)
    for i in range(length):
        if input[i].isspace():
            count += 1
    return count


def get_sentences(input):
    count = 0
    length = len(input)
    for i in range(length):
        if input[i] == '!' or input[i] == '?' or input[i] == '.':
            count += 1
    return count


def get_letters(input):
    count = 0
    length = len(input)
    for i in range(length):
        if input[i].isalpha():
            count += 1
    return count


main()

