import sys
from collections import deque

def run():
    N=int(sys.stdin.readline().strip())

    graphSize=2*N+2;
    graph = [set() for x in range(graphSize)]

    for i in range(N):
        graph[graphSize-2].add(i)
        graph[N+i].add(graphSize-1)

    for i in range(N):
        goals = sys.stdin.readline().split()
        for j in range(1, len(goals)):
            currentGoal=int(goals[j])
            graph[i].add(N+currentGoal)

    hk = HopcroftKarp()

    print(N-hk.matchingHopcroftKarp(graph, graphSize-2, graphSize-1))


class HopcroftKarp(object):

    def getBfsTree(self, graph, source, target):
        n=len(graph)
        used= [-1 for x in range(n)]
            
        result = [set() for x in range(n)]
        
        q= deque()
            
        used[source]=0
        q.append(source)
        
        while q:
            current=q.pop()
            if(current==target):
                return result
                    
            currentDist=used[current]
            for _next in graph[current]:
                if used[_next] == -1:
                    used[_next] = currentDist+1
                    q.append(_next)
                    
                if used[_next]==currentDist+1:
                    result[current].add(_next)
            
            
            #//no path to target:
        return None
		
    def dfs(self, graph, bfsTree, source,  target, used):
        if source==target:
            return True
			
        used[source]=True
        for _next in bfsTree[source]:
            if not used[_next] and self.dfs(graph, bfsTree, _next, target, used):
                graph[source].remove(_next)
                graph[_next].add(source)
                return True
            
        
        return False
	
		
    #//matching with hopcroft-karp O(m*sqrt(n))
    def matchingHopcroftKarp(self, graph, source, target):
        result=0
        n=len(graph)
        used=[False for x in range(n)]
        while True:
            
            bfsTree=self.getBfsTree(graph, source, target);
            if bfsTree==None:
                return result

            for x in range(n):
                used[x] = False
            while self.dfs(graph, bfsTree, source, target, used):
                result+=1
				

run()
