import csv

counter = 0

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    for line in reader:
        title = line['title'].strip().lower()
        if "office" in title:
            counter += 1
print(f"Number of people how likes office: {counter}")