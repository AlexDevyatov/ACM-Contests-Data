import sys, heapq
def run():
    N, P, M, G, T = [int(x) for x in sys.stdin.readline().split()]
    
    additionalTime=0
    placesToVisit = set()
    placesToVisit.add(0);#//start in Athen
    for i in range(P):
            place = sys.stdin.readline().split()
            placesToVisit.add(int(place[0]))
            additionalTime += int(place[1])
    
    graph = [[] for x in range(N)]
		  
    for i in range(M):
        _from, to, w  = [int(x) for x in sys.stdin.readline().split()]
        graph[_from].append((w,to))
        graph[to].append((w,_from))
		 
    dists=reduceGraph(graph, placesToVisit)
		  
		  
    times=runTSP(dists,T);
    
    if times[0]+additionalTime<=G:
        print("possible without taxi")
    elif(times[1]+additionalTime<=G):
        print("possible with taxi")
    else:
        print("impossible")
	
	
def reduceGraph(graph, places):
    n = len(places)
    result = [[0 for a in range(n)] for b in range(n)]
    ind1=0
    for start in places:
            dists=dijkstra(graph, start)
            ind2=0
            for end in places:
                 result[ind1][ind2]=dists[end];
                 ind2 += 1
            ind1+=1
    return result

def dijkstra(graph, start):
    N = len(graph)
    dists = [2**31-1 for x in range(N)]
    #//int[0] - weight -> other information int[1]...int[?]
    q = []
    
    #//costs[0][0]=0;
    q.append((0, start))
    dists[start] = 0
    while q:
        akt=heapq.heappop(q);
        current=akt[1];
        curDist=akt[0];
        if curDist!=dists[current]:
            continue;# //already processed
        for edge in graph[current]:
            _next=edge[1]
            nextDist=dists[current]+edge[0];
            if dists[_next]>nextDist:
                dists[_next]=nextDist;
                heapq.heappush(q, (nextDist, _next))
    return dists;
	
	
	
# def ini3DArrayWithMaxInt(ar):
#     for subar in ar:
#         for subsubar in subar:
#             Arrays.fill(subsubar, Integer.MAX_VALUE)

def bitCount(int_type):
    count = 0
    while(int_type):
        int_type &= int_type - 1
        count += 1
    return(count)

            
def  runTSP(dists, taxiTime):
    n = len(dists)
    MAX=1<<n;
    MAX_VALUE=2**31-1
    curBest = [[[MAX_VALUE for z in range(MAX)]for y in range(n)]for x in range(2)]
    #nextBest = [[[MAX_VALUE for z in range(MAX)]for y in range(n)]for x in range(2)]
    
    curBest[0][0][1]=0;#//start in 0
    
    for j in range(1, n):#{//number of visited sides
        nextBest = [[[MAX_VALUE for z in range(MAX)]for y in range(n)]for x in range(2)]
        for curState in range((1<<j)-1, MAX):
            if(bitCount(curState)!=j):
                continue;

            for taxiUsed in range(2):
                for curPos in range(n):
                    if(curBest[taxiUsed][curPos][curState]==MAX_VALUE):
                        continue;
                    curValue=curBest[taxiUsed][curPos][curState];
                    for i in range(n):
                        if(i==curPos or dists[curPos][i]==MAX_VALUE):
                            continue;
                        nextState = curState|(1<<i);
                        nextBest[taxiUsed][i][nextState]=min(nextBest[taxiUsed][i][nextState], curValue+dists[curPos][i])
                        if(taxiUsed==0):#//we could take taxi
                            nextBest[1][i][nextState]=min(nextBest[1][i][nextState], curValue+taxiTime);

				   
		   
		
        curBest, nextBest = nextBest, curBest
	   
    res = [MAX_VALUE, MAX_VALUE]
	   
    for taxi in range(2):
        for i in range(n):
            if(curBest[taxi][i][MAX-1] != MAX_VALUE):
                    res[taxi] = min(res[taxi], curBest[taxi][i][MAX-1]+dists[i][0]);
                    if(taxi==0):
                        res[1]= min(res[1], curBest[0][i][MAX-1]+taxiTime);# //last ride with taxi
			   
    return res;

run()
