def main():

    cardNumber = getCardNumber()
    cardLenght = len(cardNumber)
    checksum = validateСardNumber(cardNumber)

    if checksum == False:
        print("INVALID")
        return 1

    startNumbers = ""
    for i in range(2):
      startNumbers += cardNumber[i]


    if startNumbers == "34" or startNumbers == "37" and cardLenght == 15:
        print("AMEX")
    elif startNumbers == "51" or startNumbers == "52" or startNumbers == "53" or startNumbers == "54" or startNumbers == "55" and cardLenght == 16:
        print("MASTERCARD")
    else:
        print("VISA")

def validateСardNumber(cardNumber):
    cardLenght = len(cardNumber)
    reverseCardNumberList = list()

    for i in range(cardLenght):
        reverseCardNumberList.append(cardNumber[i])

    reverseCardNumberList.reverse()

    multipliedNumbersList = list()
    sum = 0

    # Умножение каждой второй цифры на 2
    for i in range(1, cardLenght, 2):
        multipliedNumber = int(reverseCardNumberList[i]) * 2
        multipliedNumbersList.append(str(multipliedNumber))


    # Сложение всех цифр умноженных на 2
    for number in multipliedNumbersList:
        if len(number) != 2:
            sum += int(number)
        else:
            for i in range(2):
                sum += int(number[i])

    # Сложение чисел которые не были умножены на 2
    for i in range(0, cardLenght, 2):
        sum += int(reverseCardNumberList[i])

    if sum % 10 == 0:
        return True
    else:
        return False

def getCardNumber():
    try:
        cardNumber = int(input("Enter card number: "))
    except ValueError:
        print("That's not a number")
        exit(1)
    return str(cardNumber)
main()

