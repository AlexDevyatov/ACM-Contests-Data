import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;
import java.util.TreeSet;


public class BountyHunterHKEgor {

	

	public static void main(String[] args)throws Exception{
        new BountyHunterHKEgor().run();
    }

	



	@SuppressWarnings("unchecked")
	private void run() throws Exception{

		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));


		  int N=Integer.parseInt(reader.readLine());	  

		  int graphSize=2*N+2;
		  Set<Integer>[] graph=new Set[graphSize];

		  for(int i=0;i<graphSize;i++)
			graph[i]=new TreeSet<Integer>();

			

		  for(int i=0;i<N;i++){
			  graph[graphSize-2].add(i);
			  graph[N+i].add(graphSize-1);
		  }


		  for(int i=0;i<N;i++){

			  String[] goals=reader.readLine().split(" ");
			  
			  for(int j=1;j<goals.length;j++){
				  int currentGoal=Integer.parseInt(goals[j]);
				  graph[i].add(N+currentGoal);
			  }
		  }

		  HopcroftKarp hk=new HopcroftKarp();

		  System.out.println(N-hk.matchingHopcroftKarp(graph, graphSize-2, graphSize-1));
	}



	public class HopcroftKarp {

	    
		
		 Set<Integer>[] getBfsTree(Set<Integer>[] graph, int source, int target){
			int n=graph.length;
			int[] used=new int[n];
			Arrays.fill(used, -1);
			
			@SuppressWarnings("unchecked")
			Set<Integer>[] result=new Set[n];
			for(int i=0;i<n;result[i++]=new TreeSet<Integer>());
			Queue<Integer> q=new LinkedList<Integer>();
			
			used[source]=0;
			q.offer(source);
			while(!q.isEmpty()){
				int current=q.poll();
				if(current==target)
					return result;
				
				int currentDist=used[current];
				for(int next:graph[current]){
					if(used[next]==-1){
						used[next]=currentDist+1;
						q.offer(next);
					}
					if(used[next]==currentDist+1)
						result[current].add(next);
				}
			}
			//no path to target:
			return null;
		}
		
		 boolean dfs(Set<Integer>[] graph, Set<Integer>[] bfsTree, int source,  int target, boolean[] used){
			if(source==target)
				return true;
			
			used[source]=true;
			for(int next: bfsTree[source]){
				if(!used[next] && dfs(graph, bfsTree, next, target, used)){
					graph[source].remove(next);
					graph[next].add(source);
					return true;
				}
			}
			return false;
		}
	
		
		//matching with hopcroft-karp O(m*sqrt(n))
		int matchingHopcroftKarp(Set<Integer>[] graph, int source, int target){
			int result=0;
			int n=graph.length;
			boolean[] used=new boolean[n];
			while(true){
				
				Set<Integer>[] bfsTree=getBfsTree(graph, source, target);
				if(bfsTree==null) 
					return result;

				
				Arrays.fill(used, false);
				while(dfs(graph, bfsTree, source, target, used))
					result++;
				
			}
			
		}
	}
}
