import random
import sys

MAX_N = 10**9
MAX_M = 10**9

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


    


def gen_rand_cases(mods, short_desc=None):
    for mod in mods:
        save_case(random.randint(1, MAX_N), mod, short_desc=short_desc)
    

# iterates of phi have many prime factors with exponent = 1
MANY_SINGLE_PRIMES = [
    328511998,
    164255999,
    143700478
]

# iterates of phi have many prime factors with exponent > 1
MANY_REPEATED_PRIMES = [
    846519025,
    810417949,
    673980839
]

# iterates of phi have many values of form 2*p for p primex
MANY_NEAR_PRIME = [
    298172158,
    277021438,
    143700478
]

# max #iterations of phi to reach 1 (30 iterations)
LONG_CHAINS = [
    541073537, # first
    966976267, # avoids powers of 2 for as long as possible
    943083809, # avoids powers of 2 for as long as possible
    999958529  # last
]

# max #iterations until we reach power of 2 (18 iterations)
LONG_CHAINS_NO_POW2 = [
    387420489, # first
    903981141, # last
]

#
MAX_FACTOR_COST = [
    999145019,
    997514723
]

def main():
    random.seed(12345)
    
    # small n
    save_case(1, 1, short_desc='n1_m1')
    save_case(1, MAX_M, short_desc='n1_mmax')
    save_case(2, MAX_M, short_desc='n2_mmax')
    save_case(3, MAX_M, short_desc='n3_mmax')
    save_case(4, MAX_M, short_desc='n4_mmax')
    save_case(5, MAX_M, short_desc='n5_mmax')

    # a few small random cases
    for i in range(3):
        save_case(random.randint(1, 100), random.randint(1, 1000),
                  short_desc='randsmall')

    # a few uniformly random cases
    gen_rand_cases([random.randint(1, MAX_M) for _ in range(3)],
                   short_desc='rand')

    # extreme cases with max N
    save_case(MAX_N, 1, short_desc='nmax_m1')
    save_case(MAX_N, MAX_M, short_desc='nmax_mmax')

    # one param maxed out the other random
    save_case(MAX_N, random.randint(1, MAX_M),
              short_desc='nmax_mrand')
    save_case(MAX_N, random.randint(1, MAX_M),
              short_desc='nmax_mrand')
    save_case(random.randint(1, MAX_N), MAX_M,
              short_desc='nrand_mmax')
    save_case(random.randint(1, MAX_N), MAX_M,
              short_desc='nrand_mmax')
    
    # special moduli
    gen_rand_cases(MANY_SINGLE_PRIMES,
                   short_desc='many_single_primes')
    gen_rand_cases(MANY_SINGLE_PRIMES,
                   short_desc='many_single_primes')
    gen_rand_cases(MANY_REPEATED_PRIMES,
                   short_desc='many_rep_primes')
    gen_rand_cases(MANY_REPEATED_PRIMES,
                   short_desc='many_rep_primes')
    gen_rand_cases(MANY_NEAR_PRIME,
                   short_desc='many_2primes')
    gen_rand_cases(MANY_NEAR_PRIME,
                   short_desc='many_2primes')
    gen_rand_cases(LONG_CHAINS,
                   short_desc='long_chain')
    gen_rand_cases(LONG_CHAINS,
                   short_desc='long_chain')
    gen_rand_cases(LONG_CHAINS_NO_POW2,
                   short_desc='long_chain_until_2pow')
    gen_rand_cases(LONG_CHAINS_NO_POW2,
                   short_desc='long_chain_until_2pow')
    gen_rand_cases(MAX_FACTOR_COST,
                   short_desc='few_small_factors')
    gen_rand_cases(MAX_FACTOR_COST,
                   short_desc='few_small_factors')

    # powers of two
    save_case(4, 2**18, short_desc='2pow')
    save_case(4, 2**19, short_desc='2pow')
    save_case(4, 2**29, short_desc='2pow')
    save_case(5, 2**5, short_desc='2pow')
    save_case(5, 2**29, short_desc='2pow')
    save_case(6, 2**29, short_desc='2pow')
    save_case(8, 2**29, short_desc='2pow')
    save_case(10**9, 2**29, short_desc='2pow')

    # powers of five
    save_case(4, 5**12, short_desc='5pow')
    save_case(5, 5**12, short_desc='5pow')
    save_case(6, 5**12, short_desc='5pow')
    save_case(10, 5**12, short_desc='5pow')
    save_case(865000085, 5**12, short_desc='5pow')
    save_case(10**9, 5**12, short_desc='5pow')
    
    # large RSA moduli
    save_case(5, 31607*31627, short_desc='large_rsa')
    gen_rand_cases([31607*31627], short_desc='large_rsa')
    
    # large prime
    save_case(5, 999999929, short_desc='large_prime')
    gen_rand_cases([999999929], short_desc='large_prime')

    # mod = 2^28 * 3
    save_case(6, 805306368)
    save_case(10, 805306368)

    # big cycles to time out Antti's brute force period finder
    save_case(225388054, 910313102)
    save_case(437862890, 961681762)

    
if __name__=='__main__':
    main()
