from random import random as rnd

def ans(l,r):
    if l == r == 0:
        return 'Not a moose'
    elif l == r:
        return 'Even %d' % (2*r)
    else:
        return 'Odd %d' % (2*max(l,r))


def nextbool(x=0.05):
    return rnd() < x

f = 0
for l in range(20):
    for r in range(20):
        if l == r or nextbool():
            f += 1
            with open('%d.in' % f, 'w') as fin:
                with open('%d.ans' % f, 'w') as fout:
                    fin.write('%d %d\n' % (l,r))
                    fout.write('%s\n' % ans(l,r))
