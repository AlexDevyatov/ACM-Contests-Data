#!/usr/bin/env python
import random
import sys


def main(ownFile, numToWest, numToEast, timeToPass):
    numToWest = int(numToWest)
    numToEast = int(numToEast)
    timeToPass = int(timeToPass)

    random.seed(0)
    n = numToWest + numToEast
    print('%d %d' % (timeToPass, n))
    allIndices = list(range(n))
    random.shuffle(allIndices)
    direction = [x[1] for x in sorted(zip(allIndices, ['W']*numToWest + ['E']*numToEast))]
    lastTime = 0
    for d in direction:
        t = lastTime + random.randint(0, 3*timeToPass)
        lastTime = t
        irritatedTime = random.randint(0, 3*timeToPass)
        print('%c %d %d' % (d, t, irritatedTime))
    return 0

if __name__ == '__main__':
    sys.exit(main(*sys.argv))
