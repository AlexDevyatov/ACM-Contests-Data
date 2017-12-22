from random import randint
def generate_proper_interval(n, k, max_val):
    print(n, k)
    for i in range(n):
        x = [randint(0, max_val) for x in range(2)]
        x.sort()
        print(x[0], x[1])

generate_proper_interval(100000, 20000, 10 ** 9)
