def main():
    cents = get_cents()

    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25

    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10

    nickels = calculate_nickels(cents)
    cents = cents - nickels * 5

    pennies = calculate_pennies(cents)
    cents = cents - pennies * 1

    coins = quarters + dimes + nickels + pennies

    print(f"Total number of coins: {coins}")

def get_cents():
    while True:
        try:
            cents = float(input("Enter number of cents: "))
            if cents > 0:
                break
        except ValueError:
            print("That's not an float")
    return int(cents * 100)

def calculate_quarters(cents):
    quarters = 0
    while (cents >= 25):
        cents -= 25
        quarters += 1
    return quarters

def calculate_dimes(cents):
    dimes = 0
    while (cents >= 10):
        cents -= 10
        dimes += 1
    return dimes

def calculate_nickels(cents):
    nickels = 0
    while (cents >= 5):
        cents -= 5
        nickels += 1
    return nickels

def calculate_pennies(cents):
    pennies = 0
    while (cents >= 1):
        cents -= 1
        pennies += 1
    return pennies

main()