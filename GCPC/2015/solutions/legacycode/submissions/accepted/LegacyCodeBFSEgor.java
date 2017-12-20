import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;


public class LegacyCodeBFSEgor {
	
	public static void main(String[] args)throws Exception{
        new LegacyCodeBFSEgor().run();
    }
	
	
	private void run() throws Exception{
		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
		  
		  
		  int N=Integer.parseInt(reader.readLine());
		  
		  @SuppressWarnings("unchecked")
		  List<Integer>[] graph=new List[N];
		  for(int i=0;i<N;graph[i++]=new LinkedList<Integer>());
		  
		  
		  //fill the transposed graph:
		  MethodTracker tracker=new MethodTracker();
		  
		  for(int i=0;i<N;i++){
			  String[] description=reader.readLine().split(" ");
			  int currentGoal=tracker.getIDforName(description[0]);
			  
			  String line=reader.readLine();
			  if(line.isEmpty())
				  continue;

			  String[] users=line.split(" ");

			  for(String user:users)
				  graph[tracker.getIDforName(user)].add(currentGoal);
		  }
		  
		  System.out.println(getUnusedCnt(graph, tracker.getProgramIDs()));
	}
	
	
	int getUnusedCnt(List<Integer>[] graph, Set<Integer> starts){
		int N=graph.length;
		boolean[] visited=new boolean[N];
		Arrays.fill(visited, false);
		
		Queue<Integer> q=new LinkedList<Integer>();
		for(int i:starts){
			visited[i]=true;
			q.offer(i);
		}
		
		while(!q.isEmpty()){
			int current=q.poll();
			for(int next: graph[current])
				if(!visited[next]){
					visited[next]=true;
					q.offer(next);
				}
		}
		
		return findNotVisited(visited);

	}
	
	int findNotVisited(boolean[] visited){
		int res=0;
		for(boolean v: visited)
			if(!v)
				res++;
		
		
		return  res;
	}
	
	private class MethodTracker{
		private Map<String, Integer> known;
		
		private Set<Integer> programIDs;
		
		Set<Integer> getProgramIDs(){
			return programIDs;
		}
		
		MethodTracker(){
			known=new HashMap<String, Integer>();
			programIDs=new HashSet<Integer>();
		}
		
		int getIDforName(String name){
			Integer index=known.get(name);
			int result=0;
			if(index==null){
				result=known.size();
				
				known.put(name, result);
				
				if(isPROGRAM(name))
					programIDs.add(result);
			}
			else{
				result=index;
			}
			
			return result;
		}
		
		private boolean isPROGRAM(String name){
			return name.endsWith("::PROGRAM");
		} 
	}
	
}
