import sys

numbers = [32, 64, 134, 2, 16]

if 64 in numbers:
    print("found")
    sys.exit(0)
print("Not found")
sys.exit(1)