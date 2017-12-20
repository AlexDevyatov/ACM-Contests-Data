from __future__ import print_function
try:
    import __builtin__
    input = getattr(__builtin__, 'raw_input', input)  # Python 3 (PEP 3111)
except:
    pass


from math import *

a, N = input().split(" ")
a, N = float(a), int(N)

point = [input().split(" ") for _ in range(N)]
point = [(int(x), int(y)) for x, y in point]

def sub(a, b):
    return (a[0] - b[0], a[1] - b[1])

def cross(a, b):
    return a[0] * b[1] - a[1] * b[0]

area_twice = lambda i: abs(cross(sub(point[i-1], point[0]),
                                 sub(point[i],   point[0])))
area_twice = [area_twice(i) for i in range(2, N)]
area_twice = sum(area_twice)

def cut_area_twice(j):
    """calculate (twice the) cut area but assume s == 1
       (divide result by s**2 for fix)"""
    i = (j - 1 + N) % N
    k = (j + 1) % N
    a, b = sub(point[i], point[j]), sub(point[k], point[j])
    return abs(cross(a, b))

cut_twice = [cut_area_twice(i) for i in range(N)]

# A - sum(cut) / s**2 = a * A
s = sqrt(sum(cut_twice) / (area_twice * (1.0-a)))
print(s)
