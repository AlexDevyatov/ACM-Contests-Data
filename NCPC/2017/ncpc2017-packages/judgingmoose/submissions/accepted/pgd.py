from sys import stdin

l, r = map(int, stdin.readline().strip().split())
if l == r == 0:
    print('Not a moose')
elif l == r:
    print('Even %d' % (2*r))
else:
    print('Odd %d' % (2*max(l,r)))
