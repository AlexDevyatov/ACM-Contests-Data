import sys

line = sys.stdin.readline()
line = line[0:-1]

pes = line[0::3]
ees = line[1::3]
res = line[2::3]

pes = len([p for p in pes if p != 'P'])
ees = len([e for e in ees if e != 'E'])
res = len([r for r in res if r != 'R'])

print pes+ees+res
