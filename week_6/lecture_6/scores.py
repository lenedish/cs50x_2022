def main():
    scores = []

    for i in range(3):
        scores.append(int(input(f"Score {i}: ")))

    average = sum(scores) / len(scores)
    print(f"Averafe: {average}")

main()
