import os
import sys
import random

MAX_W = 500
MAX_H = 500
MAX_D = 10**6

CASE = 8
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

def save_case(grid, r, c, short_desc=None, long_desc=None):
    h = len(grid)
    w = len(grid[0])
    sys.stderr.write('save_case %d x %d shortdesc %s\n' % (h, w, short_desc))
    f = next_file(short_desc, long_desc)
    f.write('%d %d\n' % (h, w))
    for row in grid:
        f.write('%s\n' % ' '.join(map(str, row)))
    f.write('%d %d\n' % (r, c))
    f.close()

def gen_rand(w, h, pos_prob = 0.1):
    grid = [[0]*w for _ in range(h)]
    for i in range(h):
        for j in range(w):
            if random.random() < 0.1:
                grid[i][j] = random.randint(0, MAX_D)
            else:
                grid[i][j] = random.randint(-MAX_D, -1)
    while True:
        r = random.randint(1, h)
        c = random.randint(1, w)
        if grid[r-1][c-1] < 0:
            break
    save_case(grid, r, c, short_desc='random')

def gen_max_ans():
    w = MAX_W
    h = MAX_H
    grid = [[-MAX_D]*w for _ in range(h)]
    save_case(grid, random.randint(1, h), random.randint(1, w), short_desc='max_answer')

def gen_small_ans():
    w = MAX_W
    h = MAX_H
    r = random.randint(1, h)
    c = random.randint(1, w)
    grid = [[-MAX_D]*w for _ in range(h)]
    grid[r][c] = -1
    save_case(grid, r+1, c+1, short_desc='deep_small_answer')

def gen_min_ans():
    w = MAX_W
    h = MAX_H
    r = random.randint(1, h)
    c = random.randint(1, w)
    grid = [[-MAX_D]*w for _ in range(h)]
    grid[r][c] = -1
    for nr in [r-1, r, r+1]:
        for nc in [c-1, c, c+1]:
            if nr >= 0 and nr < h and nc >= 0 and nc < w and (nr != r or nc != c):
                grid[nr][nc] = 0
    save_case(grid, r+1, c+1, short_desc='min_answer')


def gen_detour(W, H):
    grid = [[random.randint(1, MAX_D) for _ in range(W)] for _ in range(H)]
    inf = MAX_D

    grid[0][0] = -inf
    for i in range(1, H):
        grid[i][0] = -i
        if i % 2 == 0:
            for j in range(1, i+1):
                grid[i][j] = -i
                grid[j][i] = -i
                grid[0][j] = -i

    save_case(grid, 1, 1)

def add_line(grid, r, c, dr, dc, steps, values):
    for i in range(steps):
        grid[r][c] = next(values)
        r += dr
        c += dc
    return (r, c)

def add_spiral(grid, r, c, dr, dc, steps, values, delta=2):
    sides = 0
    while steps > 0:
        (r, c) = add_line(grid, r, c, dr, dc, steps, values)
        (dr, dc) = (-dc, dr)
        sides += 1
        if sides % 2 == 0:
            steps = max(0, steps-delta)
    grid[r][c] = next(values)


def gen_spiral1(W, H):
    grid = [[0]*W for _ in range(H)]

    outer_weights = iter([-MAX_D]*(W*H/2+W+H))
    inner_weights = iter(sorted([random.randint(-MAX_D+1, -1) for _ in range(W*H/2+1)]))
    add_line(grid, 0, 0, 1, 0, H-1, outer_weights)
    add_spiral(grid, H-1, 0, 0, 1, W-1, outer_weights)
    add_line(grid, 0, 1, 1, 0, H-2, inner_weights)
    add_spiral(grid, H-2, 1, 0, 1, W-3, inner_weights)

    save_case(grid, 1, 2, short_desc='spirals')


def gen_spiral2(W, H):
    grid = [[0]*W for _ in range(H)]

    outer_weights = iter([random.randint(-MAX_D, -MAX_D/2)]*(W*H/2+W+H))
    inner_weights = iter([random.randint(-MAX_D/2, 0) for _ in range(W*H/2+1)])
    add_line(grid, 0, 0, 1, 0, H-1, outer_weights)
    add_spiral(grid, H-1, 0, 0, 1, W-1, outer_weights)
    add_line(grid, 0, 1, 1, 0, H-2, inner_weights)
    add_spiral(grid, H-2, 1, 0, 1, W-3, inner_weights)

    save_case(grid, 1, 2, short_desc='spirals')


if __name__=='__main__':

    gen_max_ans()
    gen_small_ans()
    gen_min_ans()

    gen_detour(MAX_W, MAX_H)
    gen_spiral1(MAX_W, MAX_H)
    gen_spiral2(MAX_W, MAX_H)

    for i in range(10):
        h = random.randint(1, MAX_H)
        w = random.randint(1, MAX_W)
        land_prob = random.random()/2.0
        gen_rand(w, h, land_prob)
