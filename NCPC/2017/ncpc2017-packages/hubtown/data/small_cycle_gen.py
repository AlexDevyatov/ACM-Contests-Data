import sys
import random

cyc = [(0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1), (-1, 0), (-1, 1)]
cyc = list(map(lambda t: str(t[0]) + " " + str(t[1]), cyc))
mode = "random" if len(sys.argv) < 2 else sys.argv[1]
people = cyc[0::2]
trains = cyc[1::2]

if mode == "random":
    pcap = [random.randint(1, 2) for _ in people]
    tcap = [random.randint(1, 2) for _ in trains]
elif mode == "exact":
    pcap = [random.randint(1, 2) for _ in people]
    tcap = [pcap[i] + pcap[(i+1)%len(people)] for i in range(len(people))]
elif mode == "almostexact":
    pcap = [random.randint(4, 8) for _ in people]
    tcap = [pcap[i] + pcap[(i+1)%len(people)] + random.randint(-7, 0) for i in range(len(people))]

print(sum(pcap), len(trains))
for x, t in zip(people, pcap):
    for i in range(t): print(x)
for x, t in zip(trains, tcap):
    print(x, t)
