import sys
import random

if __name__ == "__main__":
    seed, kind, length, maxelem = map(int, sys.stdin.readline().strip().split())
    random.seed(seed) 
    if kind == 0: # uniform random
        K = random.randint(1, maxelem)
        print length, K
        values = []
        for i in xrange(length):
            values.append(random.randint(0, maxelem))
        values.sort()
        for x in values:
            print x
    elif kind == 1: # edge case 1 (left)
        K = random.randint(1, maxelem)
        print length, K
        values = []
        for i in xrange(length):
            values.append(0)
        values.sort()
        for x in values:
            print x
    elif kind == 2: # edge case 2 (right)
        K = random.randint(1, maxelem)
        print length, K
        values = []
        for i in xrange(length):
            values.append(100000)
        values.sort()
        for x in values:
            print x
    elif kind == 3: # spread out and sort of even
        K = random.randint(1, maxelem)
        print length, K
        values = []
        cur = 0
        for i in xrange(length):
            values.append(cur)
            cur += 1000
            dice = random.randint(1,5)
            if dice == 1: cur -= 1
            elif dice == 2: cur += 1
            if cur >= 100000: cur = 0
        values.sort()
        for x in values:
            print x
