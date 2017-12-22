import random
import sys

MAX = 10**6

case_no = 1

def next_file(short_desc=None, long_desc=None):
    global case_no
    basename = '%02d' % case_no if short_desc is None else '%02d.%s' % (case_no, short_desc)
    case_no += 1
    if long_desc is not None:
        with open(basename + '.desc', 'w') as f:
            f.write(long_desc)
    return open(basename + '.in', 'w')

def save_case(n, m, short_desc=None, long_desc=None):
    f = next_file(short_desc=short_desc, long_desc=long_desc)
    f.write('%d %d\n' % (n, m))
    f.close()


    
def main():
    random.seed(42)

    # small random cases
    for _ in range(10):
        n = random.randint(2, 100)
        p = random.randint(2, 100)
        if p > n: (n, p) = (p, n)
        save_case(n, p, short_desc='rand_small')
    
    # extreme values
    save_case(2, 2, short_desc='nmin_pmin')
    save_case(MAX, 2, short_desc='nmax_pmin')
    save_case(MAX, MAX, short_desc='nmax_pmax')

    # uniformly random case
    for _ in range(5):
        n = random.randint(2, MAX)
        p = random.randint(2, MAX)
        if p > n: (n, p) = (p, n)
        save_case(n, p, short_desc='rand')

    prange = 10
    while prange < MAX:
        for _ in range(5):
            n = random.randint(MAX/10, MAX)
            p = random.randint(max(2, prange/10), prange)
            save_case(n, p)
        prange *= 10

if __name__=='__main__':
    main()
