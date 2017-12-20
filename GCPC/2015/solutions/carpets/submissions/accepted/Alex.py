import sys

W = None
H = None

def can_fill(filled, w, h, available_carpets):
    available_carpets.sort()
    while filled[w][h]:
        w += 1
        if w == W:
            h += 1
            w = 0
            if h == H:
                return True
    space_w = 0
    space_h = H - h
    while w + space_w < W and not filled[w + space_w][h]:
        space_w += 1
    last_w = -1
    last_h = -1
    A = len(available_carpets)
    for i in range(A-1, -1, -1):
        w_cur = available_carpets[i][0]
        h_cur = available_carpets[i][1]
        if last_w == w_cur and last_h == h_cur:
            continue
        last_w = w_cur
        last_h = h_cur
        w_cur, h_cur = h_cur, w_cur
        for ii in range(2):
            w_cur, h_cur = h_cur, w_cur
            if w_cur > space_w: continue
            if h_cur > space_h: continue
            for ww in range(w_cur):
                for hh in range(h_cur):
                    filled[w+ww][h+hh]=True
            nac = list(available_carpets)
            # print 0, i, A-1, A, len(available_carpets)
            nac[i], nac[A-1] = nac[A-1], nac[i]
            nac.pop()
            if can_fill(filled, w, h, nac):
                return True
            for ww in range(w_cur):
                for hh in range(h_cur):
                    filled[w+ww][h+hh]=False
    return False

def main():
    global W, H
    inp = [int(x) for x in sys.stdin.read().split()]
    W, H, C = inp[:3]
    avc = []
    for c in range(C):
        start = 3 + 3*c
        a, w, h = inp[start:start+3]
        if w < h:
            w, h = h, w
        for xx in range(a):
            avc.append((w, h))
    inp = None
    filled = [[False for x in range(H)] for y in range(W)]
    if can_fill(filled, 0, 0, avc):
        print("yes")
    else:
        print("no")

main()
