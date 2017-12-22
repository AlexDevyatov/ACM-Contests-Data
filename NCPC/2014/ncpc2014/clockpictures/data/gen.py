#!/usr/bin/env python3

import sys
import random
import itertools
import copy

TWOPI = 360000

def rot(l, d) :
    return [((x+d)%TWOPI+TWOPI)%TWOPI for x in l]

def pset(l1, l2, where=sys.stdout) :
    print(len(l1), file=where)
    print(*l1, file=where)
    print(*l2, file=where)

def getfiles(case) :
    return (open('secret/{}.in'.format(case), 'w'),
            open('secret/{}.ans'.format(case), 'w'))

def genxyxyz():
    fin, fans = getfiles('xyxyz')
    l = list(map(lambda i: i%2+2, range(143998)))
    l1 = rot(itertools.accumulate(l + [1,2,2]), random.randint(0, TWOPI))
    l2 = rot(itertools.accumulate(l + [2,1,2]), random.randint(0, TWOPI))
    random.shuffle(l1)
    random.shuffle(l2)
    pset(l1, l2, fin)
    print('impossible', file=fans)

def gengap() :
    fin, fans = getfiles('gap')
    l = range(0,TWOPI-2,2)
    pset(rot(l,90*1000),rot(l,270*1000), fin)
    print('possible', file=fans)

def gengapmismatch() :
    fin, fans = getfiles('gapmismatch')
    l1 = list(range(2,TWOPI//3,2)) + \
         list(range(TWOPI//3+2,TWOPI*2//3,2)) + \
         list(range(TWOPI*2//3+2,TWOPI,2))
    l2 = list(range(2,TWOPI//3,2)) + \
         list(range(TWOPI//3+2, TWOPI*2//3-2,2)) + \
         list(range(TWOPI*2//3,TWOPI,2))
    pset(rot(l1,-2), rot(l2,-2), fin)
    print('impossible', file=fans)

def genxxxz() :
    fin, fans = getfiles('xxxz')
    l1 = list(range(0,TWOPI,2))
    l2 = copy.deepcopy(l1)
    l2[-1]=TWOPI-3
    pset(l1,l2, fin)
    print('impossible', file=fans)

def genrandom(n,pos) :
    fin, fans = getfiles('random_unsorted{}_{}'.format('_pos' if pos else '', n))
    l1 = random.sample(range(TWOPI),n)
    if (pos) :
        shift = random.randrange(0,TWOPI)
        l2 = [(x+shift)%TWOPI for x in l1]
        random.shuffle(l2)
    else :
        l2 = random.sample(range(TWOPI),n)
    pset(l1, l2, fin)
    print('{}possible'.format('' if pos else 'im'), file=fans)

genxxxz()
genxyxyz()
gengap()
gengapmismatch()
genrandom(1000,False)
genrandom(5000,True)
genrandom(200000,False)
genrandom(200000,True)
