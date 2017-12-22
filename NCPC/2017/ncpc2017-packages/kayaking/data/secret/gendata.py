from random import randint, seed, shuffle
seed(42)

n = 9

f = open('{:02d}-random20.in'.format(n), 'w')
f.write('5 9 6\n')
f.write('2 501 1000\n')
c = [randint(1, 1000) for i in range(10)]
f.write(' '.join(str(a) for a in c) + '\n')
f.close()

n += 1
f = open('{:02d}-random60.in'.format(n), 'w')
f.write('20 20 20\n')
f.write('600 830 1000\n')
c = [randint(600, 1000) for i in range(30)]
f.write(' '.join(str(a) for a in c) + '\n')
f.close()

n += 1
f = open('{:02d}-random200.in'.format(n), 'w')
f.write('50 100 50\n')
f.write('600 710 1000\n')
c = [randint(900, 1000) for i in range(100)]
f.write(' '.join(str(a) for a in c) + '\n')
f.close()

n += 1
p = [20]*6 #how many of each type of pair
nn = [2*p[0]+p[1]+p[2], p[1]+2*p[3]+p[4], p[2]+p[4]+2*p[5]] #participants
s = [3*166, 4*166, 6*166] #strengths
ps = [2*s[0], s[0]+s[1], s[0]+s[2], 2*s[1], s[1]+s[2], 2*s[2]] #pair strengths
fs = 2520*166 #final speed
c = [fs//ps[i] for i in range(6) for j in range(p[i])] #canoes
shuffle(c)
f = open('{:02d}-unique_sol240.in'.format(n), 'w')
f.write(' '.join(str(a) for a in nn) + '\n')
f.write(' '.join(str(a) for a in s) + '\n')
f.write(' '.join(str(a) for a in c) + '\n')
f.close()

for v in set(c):
    i = c.index(v)
    n += 1
    c[i] -= 1
    f = open('{:02d}-single_limiting240.in'.format(n), 'w')
    f.write(' '.join(str(a) for a in nn) + '\n')
    f.write(' '.join(str(a) for a in s) + '\n')
    f.write(' '.join(str(a) for a in c) + '\n')
    f.close()
    c[i] += 1

n += 1
f = open('{:02d}-random100000.in'.format(n), 'w')
f.write('33333 33334 33333\n')
f.write('929 993 1000\n')
c = [randint(900, 1000) for i in range(50000)]
f.write(' '.join(str(a) for a in c) + '\n')
f.close()

n += 1
f = open('{:02d}-random100000.in'.format(n), 'w')
f.write('20000 60000 20000\n')
f.write('101 211 999\n')
c = [randint(47, 1000) for i in range(50000)]
f.write(' '.join(str(a) for a in c) + '\n')
f.close()

n += 1
p = [10000, 5002, 10000, 10001, 9997, 5000] #how many of each type of pair
nn = [2*p[0]+p[1]+p[2], p[1]+2*p[3]+p[4], p[2]+p[4]+2*p[5]] #participants
s = [3*165, 5*165, 6*165] #strengths
ps = [2*s[0], s[0]+s[1], s[0]+s[2], 2*s[1], s[1]+s[2], 2*s[2]] #pair strengths
fs = 3960*165 #final speed
c = [fs//ps[i] for i in range(6) for j in range(p[i])] #canoesshuffle(c)
f = open('{:02d}-unique_solution100000.in'.format(n), 'w')
f.write(' '.join(str(a) for a in nn) + '\n')
f.write(' '.join(str(a) for a in s) + '\n')
f.write(' '.join(str(a) for a in c) + '\n')
f.close()

for i in [0]:
    n += 1
    c[i] -= 1
    f = open('{:02d}-single_limiting100000.in'.format(n), 'w')
    f.write(' '.join(str(a) for a in nn) + '\n')
    f.write(' '.join(str(a) for a in s) + '\n')
    f.write(' '.join(str(a) for a in c) + '\n')
    f.close()
    c[i] += 1
