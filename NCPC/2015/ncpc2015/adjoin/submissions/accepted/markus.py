from sys import *
from collections import deque

def find_component(source, graph, marked):
    component = []
    queue = deque()
    queue.append(source)

    marked[source] = source
    while len(queue) > 0:
        v = queue.popleft()
        component.append(v)

        for nghbr in graph[v]:
            if marked[nghbr] != source:
                marked[nghbr] = source
                queue.append(nghbr)

    return component

def find_dia(component, graph):
    degree = {}
    leafs = []
    for v in component:
        degree[v] = len(graph[v])
        if degree[v] < 2:
            leafs.append(v)

    layers = 0
    explored = len(leafs)
    comp_size = len(component)
    while explored < comp_size:
        layers += 1
        new_leafs = []
        for v in leafs:
            for nghbr in graph[v]:
                degree[nghbr] = degree[nghbr]-1
                if degree[nghbr] == 1:
                    new_leafs.append(nghbr)

        leafs = new_leafs
        explored += len(leafs)

    return 2*layers + (1 if len(leafs) == 2 else 0)

N, M = map(int, stdin.readline().split())

graph = [[] for i in range(N)]
for i in range(M):
    a, b = map(int, stdin.readline().split())
    graph[a].append(b)
    graph[b].append(a)

max_dia = 0
max_radii = [0, 0, 0]
marked = [-1]*N
for v in range(N):
    if marked[v] < 0:
        component = find_component(v, graph, marked)
        dia = find_dia(component, graph)
        radius = dia/2 + dia%2
        max_dia = max(max_dia, dia)

        max_radii.append(radius)
        max_radii.sort()
        max_radii = max_radii[1:]


print max(max_dia,          
        sum(max_radii[1:])+1,   
        sum(max_radii[:2])+2)
