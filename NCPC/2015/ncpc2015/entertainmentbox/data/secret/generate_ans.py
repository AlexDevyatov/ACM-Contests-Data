from collections import deque
from os import listdir
from os.path import isfile, join


def solve(filename):
    fi = open(filename,"r")
    s = fi.readline().split()
    n, k = int(s[0]), int(s[1])
    
    
    a = []
    for i in range(n):
        inp = fi.readline().split()
	a.append((int(inp[0]), int(inp[1])))
        
    a = sorted(a, key=lambda x: x[1])
    
    q = deque()
    sol = 0
        
    for i in range(k):
        sol += 1
        q.append(a[i])
            
    for i in range(k, n):
        f = q[0]
        c = a[i]
        if f[1] <= c[0]:
            q.popleft()
            q.append(c)
            sol += 1
    
    fi.close()
    return sol


onlyfiles = [ f for f in listdir(".") if isfile(join(".",f)) ]
files_ending_with_in = [f for f in onlyfiles if f[-2:]=="in"]

for x in files_ending_with_in:
    print "Solving " + x
    ans = solve(x)
    outfile = open(x[:-2] + "ans", "w+")
    outfile.write(str(ans) + "\n")
    print x, ans
    outfile.close()
