from random import randint

def generate_uniformly(n,k,filename, max_val):
    f = open(filename, "w+")
    f.write(str(n) + " " + str(k) + "\n")
    
    for i in range(n):
        a = randint(0,   max_val-1)
        b = randint(a+1, max_val)
        f.write(str(a) + " " + str(b) + "\n")
    f.close()


def generate_proper_interval(n,k,filename, max_val, size):
    f = open(filename, "w+")
    f.write(str(n) + " " + str(k) + "\n")
    
    for i in range(n):
        a = randint(0,   max_val - size )

        f.write(str(a) + " " + str(a + size) + "\n")
    f.close()




def generate_interval_uniform(n,k,filename, max_val):
    f = open(filename, "w+")
    f.write(str(n) + " " + str(k) + "\n")
    
    intervals = []
    
    while len(intervals) < n:
        x = randint(0, max_val * max_val)
        a = x / max_val
        b = x % (max_val + 1)
        if a != b:
            intervals.append(tuple(sorted([a,b])))
        
    for e in intervals:
        f.write(str(e[0]) + " " + str(e[1]) + "\n")
    f.close()



for i in range(6):
    generate_uniformly(100,(1+i)*3,"uniform." + str(i) + ".in", 30)

for i in range(2):
    generate_uniformly(100000,(1+i)*3,"uniformlong." + str(i) + ".in", 1000)


for i in range(6):
    generate_proper_interval(100,(1+i)*3,"properlong." + str(i) + ".in", 30, 2*(i+4))

for i in range(2):
    generate_proper_interval(100000,(1+i)*3,"properlong." + str(i) + ".in", 1000, 10*(i+4))


for i in range(6):
    generate_interval_uniform(100,(1+i)*3,"uniint." + str(i) + ".in", 30)

for i in range(2):
    generate_interval_uniform(100000,(1+i)*3,"uniintlong." + str(i) + ".in", 1000)

