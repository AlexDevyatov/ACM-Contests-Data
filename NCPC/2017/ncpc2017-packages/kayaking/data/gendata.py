import os
import sys
import random

MAX_S = 1000
MIN_C = 1
MAX_C = 100000
MAX_K = 100000

CASE = 31
DEST = os.path.join(os.path.dirname(__file__), 'secret')

def next_file(short_desc=None, long_desc=None):
    global CASE
    basename = os.path.join(DEST, '%02d' % CASE)
    CASE += 1
    if short_desc is not None:
        basename += '-' + short_desc
    if long_desc is not None:
        with open(basename+'.desc', 'w') as desc_out:
            desc_out.write(long_desc)
    return open(basename+'.in', 'w')

def save_case(n, s, c, short_desc=None, long_desc=None):
    assert min(n) >= 0
    assert sum(n) == 2*len(c)
    sys.stderr.write('save_case %s, %s, %d shortdesc %s\n' % (n, s, len(c), short_desc))
    f = next_file(short_desc, long_desc)
    f.write('%s\n' % (' '.join(map(str, n))))
    f.write('%s\n' % (' '.join(map(str, s))))
    f.write('%s\n' % (' '.join(map(str, c))))
    f.close()

def gen_many_opts(f_beginner = 0.3, f_medium = 0.3):
    n = MAX_K/2
    s = [MAX_S-3, MAX_S-1, MAX_S]
    c = [MIN_C + (MAX_C-MIN_C+1)*i/n for i in range(n)]
    random.shuffle(c)
    nb = int(round(f_beginner*2*n))
    nm = int(round(f_medium*2*n))
    ne = 2*n - nb - nm
    save_case([nb, nm, ne], s, c, short_desc='many_potential_opts')

def gen_many_opts2(f_beginner = 0.3, f_medium = 0.3):
    n = MAX_K/2
    s = [1, 2, MAX_S]
#    s = [MAX_S-3, MAX_S-1, MAX_S]
    c = [MAX_C/2 + (MAX_C-MAX_C/2+1)*i/n for i in range(n)]
    random.shuffle(c)
    nb = int(round(f_beginner*2*n))
    nm = int(round(f_medium*2*n))
    ne = 2*n - nb - nm
    save_case([nb, nm, ne], s, c, short_desc='many_potential_opts')

def gen_max_ans():
    save_case([0, 0, MAX_K], [MAX_S-2, MAX_S-1, MAX_S], [MAX_C]*(MAX_K/2), short_desc='max_ans')

def gen_random(n):
    s = sorted(random.sample(range(1, MAX_S+1), 3))
    c = [random.randint(MIN_C, MAX_C) for _ in range(n)]
    n *= 2
    i = random.randint(0, n+1)
    j = random.randint(0, n+1)
    if j < i: (i, j) = (j, i)
    save_case([i, j-i, n-j], s, c, short_desc='random')

if __name__=='__main__':
    random.seed(23)

    gen_max_ans()

    gen_many_opts2()
    gen_many_opts2(0.01, 0.01)
    gen_many_opts2(0.01, 0.98)
    gen_many_opts2(0.98, 0.01)

    gen_many_opts()
    f1 = random.random()
    f2 = random.random()
    if f2 < f1: (f1, f2) = (f2, f1)
    gen_many_opts(f1, f2-f1)

    for _ in range(5):
        n = random.randint(1, MAX_K/2)
        gen_random(n)
    gen_random(MAX_K/2)
    gen_random(MAX_K/2)
    gen_random(MAX_K/2)
