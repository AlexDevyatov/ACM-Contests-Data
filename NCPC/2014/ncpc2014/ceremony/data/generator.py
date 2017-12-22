#!/usr/bin/env python

from random import seed, randint
from sys import argv
seed(None)

#
# Usage: ./generator.py (sqr|random|linear|revlinear|flat) > file.in
#

n = randint(1, 10**5)

def jigger(h):
    return map(lambda x: max(1, min(10**6, x + randint(-5, +5))), h)

def display(n, h):
    print(n)
    print(' '.join(map(str, h)))

strategies = {
    'random': (lambda x: randint(1, 10**6)),
    'sqr': (lambda x: randint(1, 10**3) ** 2),
    'linear': (lambda x: x),
    'revlinear': (lambda x: 10**6-x),
    'flat': (lambda x: 10**6 - 54321),
}

strategy = strategies['sqr']
for i in argv[1:]:
    strategy = strategies[i] if i in strategies else strategy

h = map(strategy, range(n))
h = jigger(h)
display(n, h)

