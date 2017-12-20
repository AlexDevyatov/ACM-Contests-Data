from __future__ import print_function
try:
    import __builtin__
    input = getattr(__builtin__, 'raw_input', input)  # Python 3 (PEP 3111)
except:
    pass


# converted from tobi_rho.java (by hans)

from fractions import gcd
from random import randrange, seed
seed(42)


def miller_rabin(n, accuracy=20):
    if n < 2:  return False
    if n <= 3: return True

    d = n - 1
    s = 0
    while (d & 1) == 0:
        d /= 2
        s += 1

    while accuracy:
        accuracy -= 1
        a = randrange(2, n)
        x = pow(a, d, n)
        if x == 1 or x == n-1:
            continue
        skip = False
        for r in range(1, s):
            x = pow(x, 2, n)
            if x == 1:
                return False
            if x == n-1:
                skip = True
                break
        if skip:
            continue
        return False
    return True

def factorize(cur):
    global N, ret
    if (miller_rabin(cur, 20)):
        facCnt = 0;
        while N % cur == 0:
            N /= cur
            facCnt += 1
        ret *= (1 + facCnt)
        if (N != 1):
            factorize(N)
    else:
        factor = 0
        while not factor:
            factor = rho(cur)
        factorize(factor)

def rho(n):
    k = 2
    y = randrange(0, n)
    x = y
    i = 0
    while True:
        i += 1
        x = (x * x + 2) % n
        if x == y:
            return 0
        d = gcd(n, abs(x-y))
        if d != 1:
            return d
        if i == k:
            y = x
            k *= 2


ret = 1
N = int(input())
if N != 1:
    factorize(N)
print(ret)
