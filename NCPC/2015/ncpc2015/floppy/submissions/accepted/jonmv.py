from sys import stdin, exit
canDo = True
for _ in range(int(stdin.readline())):
	line = stdin.readline().split()
	T = int(line[0])
	ok = [True] * (T + 1)
	for _ in range(int(line[1])):
		interval = stdin.readline().split()
		l = -int(interval[0]) + int(interval[1])
		dok = [False] * (T + 1)
		for i in range(T + 1):
			dok[i] = (ok[i - l] if i - l >= 0 else False) or (ok[i + l] if i + l <= T else False)
		if not True in dok:
			canDo = False
		ok = dok
print "possible" if canDo else "impossible"

