import sys
import random

cycfile = sys.argv[1]
mode = "random" if len(sys.argv) < 3 else sys.argv[2]
cyc = list(map(lambda x: x.strip(), open(cycfile).readlines()[1:]))
people = cyc[1::2]
trains = cyc[0::2]

if mode == "random":
    pcap = [random.randint(1, 200) for _ in people]
    tcap = [random.randint(1, 200) for _ in trains]
elif mode == "exact":
    pcap = [random.randint(1, 200) for _ in people]
    tcap = [pcap[i] + pcap[(i+1)%len(people)] for i in range(len(people))]
elif mode == "almostexact":
    pcap = [random.randint(100, 200) for _ in people]
    tcap = [pcap[i] + pcap[(i+1)%len(people)] + random.randint(-5, 0) for i in range(len(people))]
elif mode == "almostconstant":
    pcap = [1 for _ in people]
    tcap = [1 for _ in trains]
    pcap[random.randint(1, len(people) - 1)] = 2
    tcap[random.randint(1, len(trains) - 1)] = 2

print(sum(pcap), len(trains))
for x, t in zip(people, pcap):
    for i in range(t): print(x)
for x, t in zip(trains, tcap):
    print(x, t)
