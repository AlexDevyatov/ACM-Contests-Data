import random
import sys

MIN_L = 1
MAX_L = 10**9
MAX_N = 250000

case_no = 10

def next_file(short_desc=None, long_desc=None):
    global case_no
    basename = '%02d' % case_no if short_desc is None else '%02d.%s' % (case_no, short_desc)
    case_no += 1
    if long_desc is not None:
        with open(basename + '.desc', 'w') as f:
            f.write(long_desc)
    return open(basename + '.in', 'w')

def save_case(boxes, short_desc=None, long_desc=None, shuffle=True):
    sys.stderr.write('writing case %d with %d boxes\n' % (case_no, len(boxes)))
    f = next_file(short_desc=short_desc, long_desc=long_desc)    
    f.write('%d\n' % len(boxes))
    if shuffle:
        random.shuffle(boxes)
    for (s, t) in boxes:
        f.write('%d %d\n' % (min(s, t), max(s, t)))
    f.close()


def gen_lens(n, maxl=MAX_L):
    used = set()
    ret = []
    while len(ret) < n:
        l = random.randint(MIN_L, maxl)
        if l not in used:
            used.add(l)
            ret.append(l)
    return ret


def gen_single_cycle_comp(n, cyc_len):
    lens = gen_lens(n)
    par = []
    par.append(cyc_len-1)
    for i in range(cyc_len-1):
        par.append(i)
    for i in range(cyc_len, n):
        par.append(random.randint(0, i-1))
    boxes = [(lens[i], lens[par[i]]) for i in range(n)]
    save_case(boxes,
              short_desc='cyc%d' % cyc_len,
              long_desc = 'Single component with cycle of length %d' % cyc_len)


def gen_single_random_tree_comp(n):
    lens = gen_lens(n+1)
    par = [0]
    for i in range(1, n+1):
        par.append(random.randint(0, i-1))
    boxes = [(lens[i], lens[par[i]]) for i in range(1,n+1)]
    save_case(boxes, short_desc='randtree',
              long_desc='Single component which is a random tree')


def gen_single_binary_tree_comp(n):
    lens = gen_lens(n+1)
    par = [0]
    for i in range(1,n+1):
        par.append((i-1)/2)
    boxes = [(lens[i], lens[par[i]]) for i in range(1,n+1)]
    save_case(boxes, short_desc='binary_tree',
              long_desc='Single component which is a binary tree')


def gen_single_path(n):
    lens = gen_lens(n+1)
    par = [0]
    for i in range(1,n+1):
        par.append(i-1)
    boxes = [(lens[i], lens[par[i]]) for i in range(1,n+1)]
    save_case(boxes, short_desc='path',
              long_desc='Single component which is a path')


def gen_star(n):
    lens = [MAX_L] + gen_lens(n, MAX_L-1)
    par = [0]
    for i in range(1, n+1):
        par.append(0)
    boxes = [(lens[i], lens[par[i]]) for i in range(1,n+1)]
    save_case(boxes, short_desc='star',
              long_desc='Single component which is a star, max answer')
    

def gen_many_lens():
    n = MAX_N
    lens = gen_lens(2*n)
    save_case(zip(lens[:n], lens[n:]),
              short_desc='manylens',
              long_desc='maximum possible number of different dimensions (%d)' % (2*n))

def gen_anti_bm():
    n = MAX_N
    assert n % 2 == 0
    lens = gen_lens(n)
    vals = [(lens[0], lens[1])]
    e1 = 0
    e2 = 1
    nxt = 2
    while len(vals)+2 <= n:
        e = random.choice([e1, e2])
        vals.append((lens[nxt], lens[nxt+1]))
        ne = random.choice([nxt, nxt+1])
        vals.append((lens[e], lens[nxt+nxt+1-ne]))
        if e == e1:
            e1 = ne
        else:
            e2 = ne
        nxt += 2
    vals.append((lens[e1], lens[e2]))
    save_case(vals,
              short_desc='cycle',
              long_desc='cycle given in an order which makes a naive bipartite matching algorithm time out',
              shuffle=False)

    
def main():
    random.seed(42)

    save_case([(1,1)],
              short_desc='small',
              long_desc='Single quadratic box, minimum possible answer')
    save_case([(3,5)], short_desc='small',
              long_desc='Single non-quadratic box')
    save_case([(3,5),(3,5)],
              short_desc='small',
              long_desc='Two identical non-quadratic boxes')
    save_case([(3,3),(5,5)],
              short_desc='small',
              long_desc='Two different quadratic boxes')
    save_case([(3,3),(3,5)],
              short_desc='small',
              long_desc='One quadratic box, one non-quadratic with small dimension same as the quadratic one')

    save_case([(l,l) for l in gen_lens(MAX_N)],
              short_desc='many_squares',
              long_desc='Max # quadratic boxes')

    gen_many_lens()
    gen_star(MAX_N)
    
    gen_single_cycle_comp(MAX_N, 1)
    gen_single_cycle_comp(MAX_N, 1000)
    gen_single_cycle_comp(MAX_N, 100000)
    gen_single_cycle_comp(MAX_N, MAX_N)

    gen_single_random_tree_comp(MAX_N)
    gen_single_binary_tree_comp(MAX_N)
    gen_single_path(MAX_N)

    gen_anti_bm()
    
if __name__=='__main__':
    main()
