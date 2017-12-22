import math
import random
import sys

MAXN = 250000
MAXM = 500000

case_no = 1

def next_file(short_desc=None, long_desc=None, sub_case=None):
    global case_no
    if sub_case is None: sub_case = ''
    basename = '%02d%s' % (case_no, sub_case) if short_desc is None else '%02d%s.%s' % (case_no, sub_case, short_desc)
    sys.stderr.write('next file %s\n' % basename)
    if sub_case == '': case_no += 1
    if long_desc is not None:
        with open(basename + '.desc', 'w') as f:
            f.write(long_desc)
    return open(basename + '.in', 'w')


def save_case(n, c1, c2, calls, short_desc=None, long_desc=None, sub_case=None, shuffle=True):
    f = next_file(short_desc=short_desc, long_desc=long_desc, sub_case=sub_case)
    m = len(calls)
    if c1 > c2:
        (c1, c2) = (c2, c1)
    if shuffle:
        random.shuffle(calls)
        for i in range(m):
            if random.random() < 0.5:
                (calls[i][1], calls[i][0]) = (calls[i][0], calls[i][1])

    f.write('%d %d %d %d\n' % (n, m, c1, c2))
    f.write('\n'.join(' '.join(map(str, x)) for x in calls))
    f.write('\n')
    f.close()

    
def save_case_with_symmetries(n, c1, c2, calls, short_desc=None, long_desc=None):
    global case_no
    for i in range(4):
        sub_case = chr(ord('a')+i)
        save_case(n, c1, c2, calls, short_desc=short_desc, long_desc=long_desc, sub_case=sub_case)
        if i % 2 == 0:
            # LR flip
            c1 = n-c1
            c2 = n-c2
            calls = [[n-x+2-2*(x%2) for x in call] for call in calls]
        else:
            # TB flip
            calls = [[((x+1)^1)-1 for x in call[:2]] + call[2:] for call in calls]
    case_no += 1

                     

def gen_cross(n, c, max_len):
    while True:
        a = c + 2*random.randint(-min(c/2, max_len-1),
                                 min((n-c)/2, max_len-1))
        b = c+1 + 2*random.randint(-min(c/2, max_len-1),
                                   min((n-c)/2, max_len-1))
        if abs(a-c)+1+abs(b-c) <= max_len:
            return [a, b, c]

def gen_no_cross(n, max_len):
    L = random.randint(1, min(max_len, n/2-1))
    a = random.randint(1, n-2*L)
    return (a, a+2*L)

def random_calls(n, m, c1, c2, avoid, cross_prob=0.5, max_len=2**30):
    calls = []
    for _ in range(m):
        if random.random() > cross_prob:
            while True:
                (a, b) = gen_no_cross(n, max_len)
                if (a,b) not in avoid and (b,a) not in avoid:
                    break
            calls.append([a,b])
        else:
            while True:
                (a, b, c) = gen_cross(n, random.choice([c1, c2]), 20*max_len)
                if (a,b) not in avoid and (b,a) not in avoid:
                    break
            calls.append([a,b,c])
        avoid.add((a,b))
        #print '%d/%d seen %d max_len %d n %d' % (len(calls), m, len(avoid), max_len, n)
    return calls


def gen_max_ans(n, m, c1, c2):
    calls = []
    seen = set()
    for a in range(1, n-1):
        calls.append([a, a+2])
        seen.add((a,a+2))
    calls.append([c1,c1+1,c1])
    seen.add((c1,c1+1))
    calls.append([c2,c2+1,c2])
    seen.add((c2,c2+1))

    if len(calls) > m:
        random.shuffle(calls)
        calls = calls[:m]
    else:
        calls.extend(random_calls(n, m-len(calls), c1, c2, seen, cross_prob=0.01, max_len=5))
    save_case(n, c1, c2, calls, short_desc='max_ans')


def gen_rand_case(n, m, c1, c2, cross_prob=0.1, max_len=2**31):
    print 'gen_rand n=%d m=%d c1=%d c2=%d cross_prob=%f max_len=%d' % (n, m, c1, c2, cross_prob, max_len)
    calls = random_calls(n, m, c1, c2, set(), cross_prob=cross_prob, max_len=max_len)
    save_case(n, c1, c2, calls)


def rand_cross(n):
    c1 = 2*random.randint(1, n/2)-1
    while True:
        c2 = 2*random.randint(1, n/2)-1
        if c2 != c1:
            break
    return (c1,c2)


def gen_plant(n, m, c1, c2, top_size, bot_size, use_c1, use_c2, symmetries=False, seed=None):
    if seed is not None: random.seed(seed)
    
    desc = 'gen_plant(%d, %d, %d, %d, %d, %d, %s, %s, seed=%s, symmetries=%s)' % (n, m, c1, c2, top_size, bot_size, use_c1, use_c2, seed, symmetries)
    print desc
    
    assert top_size + bot_size + use_c1 + use_c2 <= m
    assert top_size < n/2
    assert bot_size < n/2

    _c1 = (c1+1)/2
    _c2 = (c2+1)/2

    top_pos = sorted(random.sample(range(1, n/2), top_size))
    bot_pos = sorted(random.sample(range(1, n/2), bot_size))

    top_c1_l = 0
    top_c1_r = n/2
    bot_c1_l = 0
    bot_c1_r = n/2

    top_c2_l = 0
    top_c2_r = n/2
    bot_c2_l = 0
    bot_c2_r = n/2

    for p in top_pos:
        if p < _c1:
            top_c1_l = p
        elif top_c1_r > p:
            top_c1_r = p
        if p < _c2:
            top_c2_l = p
        elif top_c2_r > p:
            top_c2_r = p

    for p in bot_pos:
        if p < _c1:
            bot_c1_l = p
        elif bot_c1_r > p:
            bot_c1_r = p
        if p < _c2:
            bot_c2_l = p
        elif bot_c2_r > p:
            bot_c2_r = p


    calls = []

    if use_c1:
        calls.append([2*random.randint(top_c1_l+1, top_c1_r)-1,
                      2*random.randint(bot_c1_l+1, bot_c1_r),
                      c1])

    if use_c2:
        calls.append([2*random.randint(top_c2_l+1, top_c2_r)-1,
                      2*random.randint(bot_c2_l+1, bot_c2_r),
                      c2])

    LB = 1
#    print '_c1 = %d, _c2 = %d, top_c1_l = %d, top_c1_r = %d, top_c2_l = %d, top_c2_r = %d' % (_c1, _c2, top_c1_l, top_c1_r, top_c2_l, top_c2_r)
    
    for i in range(top_size):
        UB = top_pos[i+1] if i+1 < top_size else n/2
#        print 'i %d: LB %d UB %d top_pos %d' % (i, LB, UB, top_pos[i])
        if not use_c1 and top_pos[i] == top_c1_l and random.random() < 0.25:
            calls.append([2*random.randint(LB, top_pos[i])-1,
                          2*random.randint(bot_c1_l+1, bot_c1_r),
                          c1])
            LB = (c1+1)/2
        elif not use_c1 and top_pos[i] == top_c1_r and random.random() < 0.25:
            calls.append([2*random.randint(top_pos[i]+1, UB)-1,
                          2*random.randint(bot_c1_l+1, bot_c1_r),
                          c1])
            LB = (calls[-1][0]+1)/2
        elif not use_c2 and top_pos[i] == top_c2_l and random.random() < 0.25:
            calls.append([2*random.randint(LB, top_pos[i])-1,
                          2*random.randint(bot_c2_l+1, bot_c2_r),
                          c2])
            LB = (c2+1)/2
        elif not use_c2 and top_pos[i] == top_c2_r and random.random() < 0.25:
            calls.append([2*random.randint(top_pos[i]+1, UB)-1,
                          2*random.randint(bot_c2_l+1, bot_c2_r),
                          c2])
            LB = (calls[-1][0]+1)/2
        else:
            calls.append([2*random.randint(LB, top_pos[i])-1,
                          2*random.randint(top_pos[i]+1, UB)-1])
            LB = (calls[-1][1]+1)/2
#        print 'add call %s' % (calls[-1])

    LB = 1
    for i in range(bot_size):
        UB = bot_pos[i+1] if i+1 < bot_size else n/2

        if not use_c1 and bot_pos[i] == bot_c1_l and random.random() < 0.25:
            calls.append([2*random.randint(LB, bot_pos[i]),
                          2*random.randint(top_c1_l+1, top_c1_r)-1,
                          c1])
            LB = (c1+1)/2
        elif not use_c1 and bot_pos[i] == bot_c1_r and random.random() < 0.25:
            calls.append([2*random.randint(bot_pos[i]+1, UB),
                          2*random.randint(top_c1_l+1, top_c1_r)-1,
                          c1])
            LB = (calls[-1][0]+1)/2
        elif not use_c2 and bot_pos[i] == bot_c2_l and random.random() < 0.25:
            calls.append([2*random.randint(LB, bot_pos[i]),
                          2*random.randint(top_c2_l+1, top_c2_r)-1,
                          c2])
            LB = (c2+1)/2
        elif not use_c2 and bot_pos[i] == bot_c2_r and random.random() < 0.25:
            calls.append([2*random.randint(bot_pos[i]+1, UB),
                          2*random.randint(top_c2_l+1, top_c2_r)-1,
                          c2])
            LB = (calls[-1][0]+1)/2
        else:
            calls.append([2*random.randint(LB, bot_pos[i]),
                          2*random.randint(bot_pos[i]+1, UB)])
            LB = (calls[-1][1]+1)/2
        
    seen = set()
    for call in calls:
        seen.add((call[0], call[1]))

    types = []
    if top_size > 0:
        types.extend([-1]*top_size)
    if bot_size > 0:
        types.extend([-2]*bot_size)
    if use_c1 or (top_size > 0 and bot_size > 0):
        types.append(c1)
    if use_c2 or (top_size > 0 and bot_size > 0):
        types.append(c2)

    while len(calls) < m:
        typ = random.choice(types)
        c = None
        if typ == -1:
            p = random.choice(top_pos)
            (a, b) = (2*random.randint(1,p)-1,
                      2*random.randint(p+1, n/2)-1)
        elif typ == -2:
            p = random.choice(bot_pos)
            (a, b) = (2*random.randint(1,p),
                      2*random.randint(p+1, n/2))
        elif typ == c1:
            c = c1
            if use_c1:
                (a, b) = (2*random.randint(1, n/2)-1,
                          2*random.randint(1, n/2))
            else:
                a_cand = []
                b_cand = []
                if top_c1_l > 0:
                    a_cand.append(2*random.randint(1, top_c1_l)-1)
                if top_c1_r < n/2:
                    a_cand.append(2*random.randint(top_c1_r+1, n/2)-1)
                if bot_c1_l > 0:
                    b_cand.append(2*random.randint(1, bot_c1_l))
                if bot_c1_r < n/2:
                    b_cand.append(2*random.randint(bot_c1_r+1, n/2))
                (a, b) = (random.choice(a_cand), random.choice(b_cand))
        
        elif typ == c2:
            c = c2
            if use_c2:
                (a, b) = (2*random.randint(1, n/2)-1,
                          2*random.randint(1, n/2))
            else:
                a_cand = []
                b_cand = []
                if top_c2_l > 0:
                    a_cand.append(2*random.randint(1, top_c2_l)-1)
                if top_c2_r < n/2:
                    a_cand.append(2*random.randint(top_c2_r+1, n/2)-1)
                if bot_c2_l > 0:
                    b_cand.append(2*random.randint(1, bot_c2_l))
                if bot_c2_r < n/2:
                    b_cand.append(2*random.randint(bot_c2_r+1, n/2))
                (a, b) = (random.choice(a_cand), random.choice(b_cand))

        else:
            assert False

        if (a,b) not in seen and (b,a) not in seen:
            seen.add((a,b))
            if c is None:
                calls.append([a, b])
            else:
                calls.append([a, b, c])
            

    calls.extend(random_calls(n, m-len(calls), c1, c2, seen, cross_prob=0.01))

    if symmetries:
        save_case_with_symmetries(n, c1, c2, calls, short_desc='planted', long_desc=desc)
    else:
        save_case(n, c1, c2, calls, short_desc='planted', long_desc=desc)

    
        
HAND_CRAFTED = [
'''
4 4 1 3
1 2 1
1 3
2 4
3 4 3
''', '''
4 4 1 3
1 2 3
1 3
2 4
3 4 3
''', '''
12 8 3 9
1 2 3
1 6 3
5 2 3
5 6 3
7 8 9
7 12 9
11 8 9
11 12 9
''', '''
100 10 9 59
9 29
19 39
29 49
10 30
20 40
30 50
25 16 9
15 26 9
45 56 59
55 46 59
''', '''
100 10 19 89
20 40
38 60
50 80
70 100
60 89 89
19 39
37 59
49 79
69 99
59 90 89
''', '''
14 8 5 9
3 6 5
3 7
4 8
4 5 5
11 7
11 10 9
12 9 9
12 8
''', '''
32 6 11 31
26 31 31
3 8 11
2 16
14 20
16 24
22 28
''', '''
16 6 7 9
1 13
13 14 7
2 3 7
5 16 9
13 16 9
4 11 9
'''
]




def crafted_cases():
    '''Some hand-written cases.'''
    
    for CASE in HAND_CRAFTED:
        f = next_file(short_desc='crafted')
        f.write(CASE.lstrip('\n'))
        f.close()


def non_nested1():
    """Lots of non-nested crossing calls."""
    n = MAXN
    c1 = n/2-1
    c2 = n/2+1
    
    c1_calls = []
    c2_calls = []

    l = 1
    r = c1+3
    while l < c1 and r <= n:
        c1_calls.append([l, r, c1])
        l += 2
        r += 2

    l = n-1
    r = c1+1
    while l > c1 and r <= n:
        c1_calls.append([l, r, c1])
        l -= 2
        r += 2

    c2_calls = []

    l = 1
    r = c2-1
    while l < c2 and r > 1:
        c2_calls.append([l, r, c2])
        l += 2
        r -= 2

    l = n-1
    r = c2+1
    while l > c2 and r > 1:
        c2_calls.append([l, r, c2])
        l -= 2
        r -= 2

    rem = MAXM - len(c1_calls) - len(c2_calls)

    top_calls = [[2*i+1, n+1-n/10+2*i] for i in range(n/20)]
    bot_calls = [[2*i+2, n+2-n/10+2*i] for i in range(n/20)]
   
    save_case(n, c1, c2, top_calls+bot_calls+c1_calls+c2_calls, short_desc='non_nested', shuffle=False)

    
def non_nested2():
    """Lots of non-nested crossing calls."""
    n = MAXN
    c1 = 1
    c2 = n-1
    
    c1_calls = []
    c2_calls = []

    l = 1
    r = n
    while l < n and r > 2:
        c1_calls.append([l, r, c1])
        l += 2
        r -= 2

    l = 1
    r = n-2
    while l < n and r > 1:
        c2_calls.append([l, r, c2])
        l += 2
        r -= 2

    rem = MAXM - len(c1_calls) - len(c2_calls)

    top_calls = [[2*i+1, n+1-n/10+2*i] for i in range(n/20)]
    bot_calls = [[2*i+2, n+2-n/10+2*i] for i in range(n/20)]
   
    save_case(n, c1, c2, top_calls+bot_calls+c1_calls+c2_calls, short_desc='non_nested', shuffle=True)



def use3():
    n = MAXN
    c1 = 1 + 4*int(n/16)+2
    c2 = c1 + 4*int(n/8)
    top_calls = [[i, i+4] for i in range(1, n, 4) if i+4 < n]
    bot_calls = [[i+1, j+1] for (i, j) in top_calls]
    cross_calls = [[c1-2, c1+1, c1],
                   [c1-1, c1, c1],
                   [c2+2, c2+1, c2],
                   [c2-1, c2, c2]]
    save_case_with_symmetries(n, c1, c2, top_calls+bot_calls+cross_calls, short_desc='use3')

    
def use4():
    n = MAXN
    c1 = 1 + 4*int(n/16)+2
    c2 = c1 + 4*int(n/8)
    top_calls = [[i, i+4] for i in range(1, n, 4) if i+4 < n]
    bot_calls = [[i+1, j+1] for (i, j) in top_calls]
    cross_calls = [[c1-2, c1+1, c1],
                   [c1-1, c1, c1],
                   [c2+2, c2+1, c2],
                   [c2+3, c2, c2]]
    save_case(n, c1, c2, top_calls+bot_calls+cross_calls, short_desc='use4', shuffle=True)

    
def special_cases_large():
    '''A bunch of carefully selected random cases that appear to provide good coverage.'''

    gen_plant(244558, 478655, 93069, 222679, 3, 102593, False, False, seed=217211048, symmetries=True)

    gen_plant(242412, 487991, 28725, 26011, 10982, 7, True, False, seed=107199096, symmetries=True)

    gen_plant(242322, 497612, 198939, 19967, 27231, 0, False, False, seed=476208233, symmetries=True)

    gen_plant(237850, 485023, 167725, 150743, 7, 1, False, False, seed=712436538, symmetries=True)

    gen_plant(239372, 483257, 114287, 74963, 8, 49879, False, False, seed=16712735, symmetries=True)

    gen_plant(248942, 488279, 218919, 122087, 7, 4, False, False, seed=909104641, symmetries=True)

    gen_plant(245978, 496664, 53073, 168805, 15041, 53731, True, False, seed=934918118, symmetries=True)

    gen_plant(242508, 485905, 106411, 134327, 77051, 8, False, True, seed=464344859, symmetries=True)

    gen_plant(239266, 492731, 198121, 128309, 12772, 14400, False, False, seed=201782801, symmetries=True)

    gen_plant(249840, 483239, 47091, 155777, 2, 4, True, False, seed=92475837, symmetries=True)

    
    
def special_cases_small():
    gen_plant(2396, 4895, 2299, 1631, 63, 5, True, False, seed=97299075, symmetries=True)

    gen_plant(4968, 9894, 2025, 4157, 658, 6, False, False, seed=587543107, symmetries=True)

    gen_plant(4932, 9621, 3919, 4887, 1, 59, True, False, seed=863958837, symmetries=True)

    gen_plant(4912, 9867, 1081, 1079, 61, 0, True, False, seed=378888759, symmetries=True)

    gen_plant(4882, 9975, 2143, 1373, 520, 926, False, False, seed=658385518, symmetries=True)

    gen_plant(1246, 2487, 1209, 599, 182, 10, False, False, seed=76445105, symmetries=True)
    
    
def basic_cases():
    '''Some basic cases.'''
    
    random.seed(42)
        
    # Max size cases with various properties

    # Max possible answer [min(n, m)]
    (c1, c2) = rand_cross(MAXN)
    gen_max_ans(MAXN, MAXM, c1, c2)

    # All calls across the street
    gen_rand_case(MAXN, MAXM, 1, MAXN-1, 1.0)

    # Lots of non-nested crossing intervals
    non_nested1()
    non_nested2()

    # Big cases where Jimmy's solution needs 3 resp. 4 additional
    # devices to cover the tails.
    use3()
    use4()
    
    # Few (roughly sqrt(m)) calls across the street
    (c1, c2) = rand_cross(MAXN)
    gen_rand_case(MAXN, MAXM, c1, c2, 1.0/math.sqrt(MAXM), MAXN/100)

    # Uniformly random
    (c1, c2) = rand_cross(MAXN)
    gen_rand_case(MAXN, MAXM, c1, c2)


def random_cases():
    """A bunch of medium random cases, maybe we'll catch something we
    didn't catch with the more carefully designed cases."""
    for i in range(40):
        n = 2*random.randint(50, 500)
        m = random.randint(100, min(10000, n*(n-1)/3))
        (c1, c2) = rand_cross(n)
        cross_prob = random.random()
        max_len = random.randint(10, n)
        gen_rand_case(n, m, c1, c2, cross_prob=cross_prob, max_len=max_len)
    
    
def lots_of_cases():
#    random.seed(111111)

#    for i in range(100):
    for i in range(20000):
        n = 2*random.randint(95*MAXN/100/2, MAXN/2)
        m = random.randint(95*MAXM/100, MAXM)
        n = 2*random.randint(95*MAXN/100/2/50, MAXN/2/50)
        m = random.randint(95*MAXM/100/50, MAXM/50)
        
        (c1, c2) = rand_cross(n)
        top_size = random.randint(0, random.choice([10, n/10, n/2-1]))
        bot_size = random.randint(0 if top_size > 0 else 1, random.choice([10, n/10, n/2-1]))
        use_c1 = random.random() < 0.20
        use_c2 = random.random() < 0.05
        seed = random.randint(1, 10**9)
        gen_plant(n, m, c1, c2, top_size, bot_size, use_c1, use_c2, seed=seed, symmetries=False)

        
def main():
    if len(sys.argv) > 1 and sys.argv[1] == 'lots':
        lots_of_cases()
    else:
        crafted_cases()
        basic_cases()
        special_cases_small()
        special_cases_large()
        random_cases()
    return


    

if __name__=='__main__':
    main()
