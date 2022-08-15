import csv

searchTitle = input("Enter title: " ).strip().lower()
counter = 0

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    for line in reader:
        title = line['title'].strip().lower()
        if searchTitle in title:
            counter += 1
print(f"{searchTitle}: {counter}")

