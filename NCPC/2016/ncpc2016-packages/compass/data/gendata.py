#!/usr/bin/env python3

import sys
import os

def rot(a,b):
    d = b-a
    if d > 180:
        d -= 360
    elif d <= -180:
        d += 360
    return d

base = 'secret'
if not os.path.exists(base):
    os.makedirs(base)
if os.path.isfile(base):
    raise IOError('delete file "secret" before continuing.')

dirs = [0, 45, 90, 173, 184, 195, 180, 270, 313, 359]
pairs = []
for i in range(len(dirs)):
    for j in range(len(dirs)):
        if dirs[i] == dirs[j]:
            continue
        pairs.append((dirs[i],dirs[j]))
pairs.append((345,345))

print('Writing %d files to %s ' % (len(pairs), base), end='')

for i in range(len(pairs)):
    if (i % 10) == 0:
        print('.', end='')
    a,b = pairs[i]
    fname_in  = '%s/%02d.in' % (base, (i+1))
    fname_out = '%s/%02d.ans' % (base, (i+1))
    ans = rot(a,b)
    with open(fname_in,  'w') as f:
        f.write('%d\n%d\n'%(a,b))
    with open(fname_out, 'w') as f:
        f.write('%d\n'% ans)
print(' done')
