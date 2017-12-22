import os
import sys
import random

MAX_N = 200000
MAX_COORD = 1000

with open(os.path.join(os.path.dirname(__file__), 'cycle_1600x1600_2152.txt')) as cycle_in:
    pts = [map(int, line.split()) for line in cycle_in.readlines()[1:]]
    CYCLE_CITIZENS = pts[1::2]
    CYCLE_TRAINS = pts[0::2]
    CYCLE_EDGES = len(pts)

CASE = 24
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

def save_case(citizens, trains, short_desc=None, long_desc=None):
    assert len(citizens) <= MAX_N
    sys.stderr.write('save_case %s, %s shortdesc %s\n' % (len(citizens), len(trains), short_desc))
    f = next_file(short_desc, long_desc)
    f.write('%d %d\n' % (len(citizens), len(trains)))
    for (x, y) in citizens:
        f.write('%d %d\n' % (x, y))
    for (x, y, c) in trains:
        f.write('%d %d %d\n' % (x, y, c))
        assert c <= len(citizens)
    f.close()


def gen_cycle(cycle_flows, noise = 0.0):
    n = CYCLE_EDGES / 2
    citizen_count = [0]*n
    train_cap = [0]*n
    for i in range(n):
        train_cap[i] = cycle_flows[2*i-2] + cycle_flows[2*i-1]
        citizen_count[i] = cycle_flows[2*i-1] + cycle_flows[2*i]

    def apply_noise(vec, noise):
        TOT = sum(vec)
        for i in range(n):
            delta = int(round(vec[i] * random.uniform(-1, 1) * noise))
            if TOT + delta > MAX_N:
                delta = MAX_N - TOT
            vec[i] += delta
            TOT += delta

    apply_noise(train_cap, noise)
    apply_noise(citizen_count, noise)

    citizens = []
    trains = []
    for i in range(n):
        max_mul = MAX_COORD / max(abs(CYCLE_CITIZENS[i][0]), abs(CYCLE_CITIZENS[i][1]))
        for _ in range(citizen_count[i]):
            mul = random.randint(1, max_mul)
#            mul = 1
            citizens.append((CYCLE_CITIZENS[i][0]*mul, CYCLE_CITIZENS[i][1]*mul))
        if train_cap[i]:
            trains.append((CYCLE_TRAINS[i][0], CYCLE_TRAINS[i][1], train_cap[i]))

    random.shuffle(citizens)
    random.shuffle(trains)
    save_case(citizens, trains, short_desc='per_cyclecaps')


def gen_constant_path(flow, noise = 0.0, start_parity = 0):
    flows = [flow] * CYCLE_EDGES
    i = 2*random.randint(0, CYCLE_EDGES/2-1) + start_parity
    for j in range(2):
        flows[i-j] = 0
    gen_cycle(flows, noise)

def gen_const_bottlenecks_cycle(flow, bottleneck_dist, noise = 0.0, start_parity = 0):
    flows = [flow] * CYCLE_EDGES
    i = 2*random.randint(0, CYCLE_EDGES/2-1) + start_parity
    flows[i] = flows[i+1] = flow/2
    j = (i + 2*bottleneck_dist - 1) % CYCLE_EDGES
    flows[j] = flows[j+1] = flow/2
    gen_cycle(flows, noise)

def gen_rand_cycle(min_flow, tot_flow, noise = 0.0):
    rem = tot_flow - min_flow*CYCLE_EDGES
    breaks = [0] + list(sorted([random.randint(0, rem) for _ in range(CYCLE_EDGES-1)])) + [rem]
    flows = []
    for i in range(CYCLE_EDGES):
        flows.append(min_flow + breaks[i+1]-breaks[i])
    assert sum(flows) == tot_flow
    gen_cycle(flows, noise)


if __name__=='__main__':
    random.seed(23)

    avg_flow = MAX_N / CYCLE_EDGES

    for noise in [0.0, 0.02, 0.5]:

        gen_constant_path(avg_flow, noise, start_parity = 0)
        gen_constant_path(avg_flow, noise, start_parity = 1)

        gen_const_bottlenecks_cycle(avg_flow, 2, noise, start_parity = 0)
        gen_const_bottlenecks_cycle(avg_flow, 2, noise, start_parity = 1)

        gen_const_bottlenecks_cycle(avg_flow, random.randint(2, CYCLE_EDGES/3), noise, start_parity = 0)
        gen_const_bottlenecks_cycle(avg_flow, random.randint(2, CYCLE_EDGES/3), noise, start_parity = 1)

        gen_rand_cycle(avg_flow/4, int(MAX_N), noise)
        gen_rand_cycle(avg_flow/4, int(MAX_N), noise)
