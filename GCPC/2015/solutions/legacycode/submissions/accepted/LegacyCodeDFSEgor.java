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



public class LegacyCodeDFSEgor {
	public static void main(String[] args)throws Exception{
        new LegacyCodeDFSEgor().run();
    }
	

	List<Integer>[] graph;
	
	@SuppressWarnings("unchecked")
	private void run() throws Exception{
		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
		  
		  
		  int N=Integer.parseInt(reader.readLine());
		  
		  
		  graph=new List[N];
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
		  
		  System.out.println(getUnusedCnt(tracker.getProgramIDs()));
	}
	
	boolean[] visited;
	
	int getUnusedCnt(Set<Integer> starts){
		visited=new boolean[graph.length];
		for(int s:starts){
			visited[s]=true;
			dfs(s);
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
	
	void dfs(int start){
		for(int next:graph[start])
			if(!visited[next]){
				visited[next]=true;
				dfs(next);
			}
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
