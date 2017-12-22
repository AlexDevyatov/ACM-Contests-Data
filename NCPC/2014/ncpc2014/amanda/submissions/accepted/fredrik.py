# Solution of problem Amanda
# Time complexity: O(m*log(m)) where m=route_count
# Stack memory size: O(n+m)
# Author: Fredrik Svensson
#
# This is not the prettiest code I've written...
# Algorithm:
#   Set the obvious lounges first.
#   The graph can now be divided into islands where setting a colour, building
#     or not, of an airport affects the rest of this island in a defined way.
#     It therefore takes O(n) to test the two possible variants for each
#     island.
#   For every non-coloured airport, try to assign a colour and choose the one
#     that generates fewest built lounges.
import sys

airports = 0
lounge = []
route_opposites = []
verified = []

def verify_lounge(a, lounge_proposal, set_verified):
    global lounge, route_opposites, verified, airports
    ret = 0
    s = [(a, lounge_proposal)]
    instack = {a: lounge_proposal}
    while len(s) > 0:
        (a, lounge_proposal) = s.pop()
        if lounge[a] == 0:
            if lounge_proposal == 1:
                ret += 1
            assert(not verified[a])
            verified[a] = set_verified
        for o in route_opposites[a]:
            if lounge[o] == lounge_proposal:
                return -1
            if (o not in instack):
                s.append((o, -lounge_proposal))
            if instack.setdefault(o, -lounge_proposal) != -lounge_proposal:
                return -1
    return ret


def doit():
    global lounge, route_opposites, verified, airports
    (airports, routes) = (int(x) for x in sys.stdin.readline().split())
    lounge = [0 for i in range(airports)]  # -1 = no lounge, 1 = lounge, 0 = not decided
    route_opposites = [[] for i in range(airports)]
    for i in range(routes):
        (a, b, c) = (int(x) for x in sys.stdin.readline().split())
        a -= 1
        b -= 1
        if c == 0:
            if lounge[a] == 1 or lounge[b] == 1:
                return -1
            lounge[a] = lounge[b] = -1
        elif c == 2:
            if lounge[a] == -1 or lounge[b] == -1:
                return -1
            lounge[a] = lounge[b] = 1
        else:
            route_opposites[a].append(b)
            route_opposites[b].append(a)
    # Verify all route_opposites
    for a in range(airports):
        for o in route_opposites[a]:
            if lounge[a] == lounge[o] and lounge[a] != 0:
                return -1
    # Fill in the rest
    ret = 0
    verified = [False for i in range(airports)]
    for i in range(airports):
        if lounge[i] == 0:
            if not verified[i]:
                reta = verify_lounge(i, -1, False)
                retb = verify_lounge(i, 1, False)
                subret = min(reta, retb)
                if subret == -1:
                    subret = max(reta, retb)
                if subret == -1:
                    return -1
                # Set as verified
                verify_lounge(i, (-1 if subret == reta else 1), True)
                ret += subret
        elif lounge[i] == 1:
            ret += 1
    return ret

ret = doit()
if (ret == -1):
    print('impossible')
else:
    print(ret)
sys.exit(0)
