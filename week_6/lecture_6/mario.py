def main():
    height = get_height()

    for i in range(height):
        for j in range(4):
            print("#", end="")
        print()


def get_height():
    while True:
        try:
            height = int(input("Height: "))
            if height > 0:
                break
        except ValueError:
            print("That's not an int")
    return height

main()
