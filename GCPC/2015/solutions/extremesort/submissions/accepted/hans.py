raw_input()
numbers = [int(x) for x in raw_input().split(' ')]

if numbers == sorted(numbers):
    print("yes")
else:
    print("no")
