def main():
    text = input("Text: ")
    text = text.lower()
    index = calculateIndex(text)

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")

def calculateIndex(text):
    words = (0 + 1)
    sentenses = 0
    letters = 0

    for i in range(len(text)):
        if text[i] == " ":
            words += 1
        elif text[i] == "." or text[i] == "!" or text[i] == "?":
            sentenses += 1
        elif text[i] >= "a" and text[i] <= "z":
            letters += 1

    l = (letters / words) * 100
    s = (sentenses / words) * 100

    index = 0.0588 * l - 0.296 * s - 15.8

    return round(index)

main()