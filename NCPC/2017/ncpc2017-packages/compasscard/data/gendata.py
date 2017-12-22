import os
import random
import sys

MAX_N = 10**5
MAX_ID = 2**31 - 1
MAX_ANGLE = 360

CASE = 1
DEST = os.path.join(os.path.dirname(__file__), 'secret')

def next_file(short_desc=None, long_desc=None):
    global CASE
    basename = os.path.join(DEST, '%02d' % CASE)
    CASE += 1
    if short_desc is not None:
        basename += '.' + short_desc
    if long_desc is not None:
        with open(basename+'.desc', 'w') as desc_out:
            desc_out.write(long_desc)
    return open(basename+'.in', 'w')

def save_case(Cards, short_desc=None, long_desc=None):
    sys.stderr.write('save_case n=%d shortdesc %s\n' % (len(Cards), short_desc))
    f = next_file(short_desc, long_desc)
    f.write('%d\n' % (len(Cards)))
    for Card in Cards:
        f.write('%d %d %d %d\n' % Card)
    f.close()


def random_ids(n):
    used = set()
    ret = []
    while len(ret) < n:
        v = random.randint(0, MAX_ID)
        if v not in used:
            used.add(v)
            ret.append(v)
    return ret

def random_angle():
    return random.randint(0, MAX_ANGLE-1)

def random_angles(n):
    return [random_angle() for _ in range(n)]

def random_case(n):
    R = random_angles(n)
    G = random_angles(n)
    B = random_angles(n)
    IDs = random_ids(n)
    save_case(zip(R, G, B, IDs), short_desc='random')


def all_equal(n):
    R = [random_angle()]*n
    G = [random_angle()]*n
    B = [random_angle()]*n
    IDs = random_ids(n)
    save_case(zip(R, G, B, IDs), short_desc='all_equal')


def many_nonzeros(n):
    IDs = random_ids(n)
    Cards = []
    for i in range(min(MAX_ANGLE-1, n)):
        Cards.append((i+1, 0, 0, IDs[len(Cards)]))
    for i in range(min(MAX_ANGLE-1, n-len(Cards))):
        Cards.append((0, i+1, 0, IDs[len(Cards)]))
    for i in range(min(MAX_ANGLE-1, n-len(Cards))):
        Cards.append((0, 0, i+1, IDs[len(Cards)]))
    for i in range(n-len(Cards)):
        Cards.append((0, 0, 0, IDs[len(Cards)]))
    random.shuffle(Cards)
    save_case(Cards, short_desc='many_nonzero')


def skewed_angles(n):
    vals = range(MAX_ANGLE)
    n -= MAX_ANGLE
    while n > 0:
        v = random.choice(range(MAX_ANGLE))
        m = (n+3)/4
        vals += [v]*m
        n -= m
    random.shuffle(vals)
    return vals

skewed_angles(MAX_N)

def skewed_random(n):
    R = skewed_angles(n)
    G = skewed_angles(n)
    B = skewed_angles(n)
    IDs = range(MAX_ID-n+1, MAX_ID+1)
    save_case(zip(R, G, B, IDs), short_desc='skewed_random')


def main():
    random.seed(42)

    save_case([(42, 13, 9, 2017)], short_desc='one_card')
    save_case([(42, 13, 9, 2017), (42, 13, 9, 2016)], short_desc='two_cards_same')
    save_case([(42, 13, 9, 2017), (13, 13, 13, 2016)], short_desc='two_cards_different')

    n = 10
    while n <= MAX_N:
        random_case(random.randint(n/10, n))
        if n/10 >= MAX_ANGLE:
            skewed_random(random.randint(n/10, n))
        n *= 10

    random_case(MAX_N)
    skewed_random(MAX_N)
    many_nonzeros(MAX_N)
    all_equal(MAX_N)



if __name__=='__main__':
    main()
