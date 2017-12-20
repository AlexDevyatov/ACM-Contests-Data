import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Collection;
import java.util.Map;
import java.util.TreeMap;
import java.util.TreeSet;

/*
 * penalize every edge on the given  shortest path with a small amount, if after this the shortest way still holds 
 *  there is no second short way.
 *  
 *  transform weights wUsed=wGiven*K+1 if they on the given path or wUsed=wGiven*K otherwise
 *  
 *  integers are enough because the biggest element in the queue is not bigger than 10.002*1.000
 *  
 *  
 *  for the shortest path dijkstra algorithms with TreeSet as PriorityQueue is used
 */

public class ChangeOfSceneryEgor {
	
	public static void main(String[] args)throws Exception{
        new ChangeOfSceneryEgor().run();
    }
	
	
	private void run() throws Exception{
		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
		  String[] nmk=reader.readLine().split(" ");
		  int N=Integer.parseInt(nmk[0]);
		  int M=Integer.parseInt(nmk[1]);
		  int K=Integer.parseInt(nmk[2]);
		  
		  String[] aShortestWay=reader.readLine().split(" ");
		  
		  graph=inizializeGraph(N);
		  int MAX=K;
		  for(int i=0;i<M; i++){
			  String[] stw=reader.readLine().split(" ");
			  int source=Integer.parseInt(stw[0])-1;
			  int target=Integer.parseInt(stw[1])-1;
			  int weight=Integer.parseInt(stw[2])*MAX;
			  addWeight(source, target, weight);
			  addWeight(target, source, weight);
		  }
		  
		  //penalize the shortest way
		  int last=Integer.parseInt(aShortestWay[0])-1;
		  for(int i=1;i<K;i++){
			  int next=Integer.parseInt(aShortestWay[i])-1;
			  incWeight(last, next);
			  incWeight(next, last);
			  last=next;
		  }
		  
		  int res=dijkstra(graph, 0, N-1);
		  System.out.println(res%MAX==K-1? "no":"yes");
	}
	
	Map<Integer, MultiEdge>[] inizializeGraph(int N){
		@SuppressWarnings("unchecked")
		Map<Integer, MultiEdge>[] graph=new Map[N];
		for(int i=0;i<N;i++)
			graph[i]=new TreeMap<Integer, MultiEdge>();
		return graph;
	}
	
	Map<Integer, MultiEdge>[] graph;
	
	void addWeight(int from, int to, int weight){
		MultiEdge edge=graph[from].get(to);
		if(edge==null){
			graph[from].put(to, new MultiEdge(weight));
		}
		else{
			edge.considerAnotherWeight(weight);
		}
	}
	
	
	void incWeight(int from, int to){
		graph[from].get(to).addWeightToMin(1);
	}
		
	

	
    public class MultiEdge{
		public int minWeight;
		public int secondMinWeight;
		
		public MultiEdge(int weight){
			this.minWeight=weight;
			this.secondMinWeight=Integer.MAX_VALUE;
		}
		
		public void considerAnotherWeight(int weight){
			if(minWeight>weight){
				secondMinWeight=minWeight;
				minWeight=weight;
			}
			else if(secondMinWeight>weight)
				secondMinWeight=weight;
		}
		
		public void addWeightToMin(int additionalWeight){
			minWeight=minWeight+additionalWeight;
			if(minWeight>secondMinWeight){
				int h=minWeight;minWeight=secondMinWeight; secondMinWeight=h;
			}
		}

	}

	int dijkstra(Map<Integer, MultiEdge>[] graph, int start, int goal){
			int n=graph.length;
			AddressablePriorityQueue pq=new AddressablePriorityQueue(n);
			boolean[] used=new boolean[n];
			
			pq.changeKey(start, 0);
			used[start]=true;
			while(! pq.isEmpty()){
				int aktIndex=pq.removeMin();
				if(aktIndex==goal) break;//early exit!
				int aktDist=pq.getCurrentDist(aktIndex);
				Collection<Map.Entry<Integer, MultiEdge>> edges=graph[aktIndex].entrySet();
				for(Map.Entry<Integer, MultiEdge> edge:edges){
					int nextGoal=edge.getKey();
					int nextDist=aktDist+edge.getValue().minWeight;
					if(pq.getCurrentDist(nextGoal)>nextDist){
						pq.changeKey(nextGoal, nextDist);
						used[nextGoal]=true;
					}
				}
			}
			
		   return pq.getCurrentDist(goal);		
	}


		private class AddressablePriorityQueue {
			private class Node implements Comparable<Node>{
				int id;
				int dist;
				
				Node(int id){
					this.id=id;
					dist=Integer.MAX_VALUE;
				}
				
				public int compareTo(Node other){
					if(dist<other.dist) return -1;
					if(dist>other.dist) return 1;
					if(id<other.id) return -1;
					if(id>other.id) return 1;
					return 0;
				}
				
				public boolean equals(Node o){
					return o.compareTo(this)==0;
				}
			}
			
			
			private Node[] nodes;
			private TreeSet<Node> tree;
			
			
			//Gibt den aktuellen Wert fuer den index aus
			public int getCurrentDist(int index){
				return nodes[index].dist;
			}
			
			
			AddressablePriorityQueue(int n){
				nodes=new Node[n];
				tree=new TreeSet<Node>();
				for(int i=0;i<n;i++){
					nodes[i]=new Node(i);
					//tree.add(nodes[i]); 
				}
			}
			
			
			
			int removeMin(){
				Node g=tree.pollFirst();
				return (g==null)? -1: g.id;
			}
			
			
			void changeKey(int id, int newKey){
				tree.remove(nodes[id]);
				nodes[id].dist=newKey;
				tree.add(nodes[id]);
			}
			
			boolean isEmpty(){
				return tree.size()==0;
			}

		}

}

