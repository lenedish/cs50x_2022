import csv
titleSet = set()
titleCount = dict()

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    for line in reader:
        title = line['title'].strip().lower()
        titleSet.add(title)

        if not title in titleCount:
            titleCount[title] = 0
        titleCount[title] += 1

# def getValue(title):
#     return title[title]

for title in sorted(titleSet, key=lambda title: titleCount[title], reverse=True):
    print(title, titleCount[title])
    