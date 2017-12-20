from __future__ import print_function
try:
    import __builtin__
    input = getattr(__builtin__, 'raw_input', input)  # Python 3 (PEP 3111)
except:
    pass


def stooge_sort(arr, a, z):
    if arr[a] > arr[z-1]:
        arr[a], arr[z-1] = arr[z-1], arr[a]
    if z - a > 2:
        t = (z - a) / 3
        stooge_sort(arr, a, z-t)
        stooge_sort(arr, a+t, z)
        stooge_sort(arr, a, z-t)


N = int(input())
data = [int(x) for x in input().split(' ')]
verify = data[:]
stooge_sort(verify, 0, len(verify))

print("yes" if data == verify else "no")
