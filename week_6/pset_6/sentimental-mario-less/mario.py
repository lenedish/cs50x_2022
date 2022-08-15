def main():
    height = get_height()
    width = height

    for i in range(1, height):
        for j in range(1, width):
            if width - i > j:
                print(" ", end="")
            else:
                print("#", end="")
        print()

# Возвращает высоту для пирамиды
def get_height():
    while True:
        try:
            height = int(input("Height: "))
            if height > 0 and height <= 8:
                break
        except ValueError:
            print("That's not an int!")
    return height + 1

main()