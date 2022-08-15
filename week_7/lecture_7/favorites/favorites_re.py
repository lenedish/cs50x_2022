import csv
import re

counter = 0

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    for line in reader:
        title = line['title'].strip().lower()
        if re.search("^(office|the.office)$", title):
            counter += 1
print(f"Number of people how likes office: {counter}")

