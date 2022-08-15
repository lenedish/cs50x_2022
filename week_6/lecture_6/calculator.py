try:
    number1 = int(input("Number 1: "))
except ValueError:
    print("It's not an int")
    exit()
try:
    number2 = int(input("Number 2: "))
except ValueError:
    print("It's not an int")
    exit()

print(number1 + number2)