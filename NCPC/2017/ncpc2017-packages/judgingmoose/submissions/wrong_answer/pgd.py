from sys import stdin

l, r = map(int, stdin.readline().strip().split())
if l == r:
    print('Even %d-point moose' % (2*r))
    exit()
else:
    print('Odd %d-point moose' % (2*max(l,r)))
    exit()
print('Not a bull moose?')
