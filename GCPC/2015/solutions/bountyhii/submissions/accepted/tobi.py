import sys
from collections import deque

def run():
    N=int(sys.stdin.readline().strip())
    graph = [set() for x in range(N)]

    for i in range(N):
        goals = sys.stdin.readline().split()
        for j in range(1, len(goals)):
            currentGoal=int(goals[j])
            graph[i].add(currentGoal)

    print(N-maxmatch(N, graph))

def maxmatch(N, graph):
    pred = [-1 for i in range(2000) ]
    ret = 0
    for j in range(N):
        mark = [ False for i in range(2000) ]
        if (match(graph, j, mark, pred)):
            ret += 1
    return ret

def match(graph, n, mark, pred):
    if (n == -1):
        return True
    for to in graph[n]:
        if (mark[to]):
            continue
        mark[to] = True
        if (match(graph, pred[to], mark, pred)):
            pred[to] = n
            return True
    return False

run()
