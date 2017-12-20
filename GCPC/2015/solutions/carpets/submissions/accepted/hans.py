from __future__ import print_function
import __builtin__
input = getattr(__builtin__, 'raw_input', input)  # as in Python 3 (PEP 3111)


import sys

W, H = [int(x) for x in input().split(' ')]
C = int(input())

carpets = []
for _ in range(C):
    a, w, h = [int(x) for x in input().split(' ')]
    if w > h:
        w, h = h, w
    for _ in range(a):
        carpets.append((w, h))
carpets = sorted(carpets)

# avoid obviously futile efforts
if sum([w*h for w, h in carpets]) < W*H:
    print('no')
    sys.exit(0)


def check(parts, carpets, depth=0):
    """parts == horizontal slices representing the floor"""
    if len(parts) == 0:   return True
    if len(carpets) == 0: return False

    # find leftmost highest slice
    p, max_ph = -1, -1
    for i, part in enumerate(parts):
        if part[1] > max_ph:
            p, max_ph = i, part[1]

    # merge with neighbors if same height
    while p+1 < len(parts) and parts[p][1] == parts[p+1][1]:
        parts[p] = (parts[p][0] + parts[p+1][0], parts[p][1])
        parts[p+1:p+2] = []

    pw, ph = parts[p]
    done = []
    for i in range(len(carpets)):
        # don't try same dimensions twice
        if carpets[i] in done: continue
        done.append(carpets[i])

        cw, ch = carpets[i]
        remaining_carpets = carpets[0:i] + carpets[i+1:]

        fitting = []
        if cw <= pw and ch <= ph:              fitting.append((cw, ch))
        if ch <= pw and cw <= ph and cw != ch: fitting.append((ch, cw))
        for w, h in fitting:
            if (w, h) == (pw, ph): new_parts = []
            elif w == pw:          new_parts = [(pw, ph - h)]
            elif h == ph:          new_parts = [(pw-w, ph)]
            else:                  new_parts = [(w, ph-h), (pw-w, ph)]

            new_parts = parts[0:p] + new_parts + parts[p+1:]
            if (check(new_parts, remaining_carpets, depth+1)):
                return True
    return False

print('yes' if check([(W, H)], carpets) else 'no')


# Let the carpets hit the floor
# Let the carpets hit the floor
# Let the carpets hit the floor
# Let the carpets hit the floooooOOOR!
