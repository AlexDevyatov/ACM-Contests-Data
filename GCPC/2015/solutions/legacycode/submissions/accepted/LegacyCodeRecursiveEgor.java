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


public class LegacyCodeRecursiveEgor {
	
	public static void main(String[] args)throws Exception{
        new LegacyCodeRecursiveEgor().run();
    }
	
	
	private void run() throws Exception{
		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
		  
		  
		  int N=Integer.parseInt(reader.readLine());
		  
		  graph=new int[N][0];
		  
		  
		  //fill the transposed graph:
		  MethodTracker tracker=new MethodTracker();
		  
		  for(int i=0;i<N;i++){
			  String[] description=reader.readLine().split(" ");
			  int goal=tracker.getIDforName(description[0]);
			  
			  String line=reader.readLine();
			  if(line.isEmpty())
				  continue;

			  String[] users=line.split(" ");
			  graph[goal]=new int[users.length];
			  int cnt = 0;
			  for(String user:users)
				  graph[goal][cnt++]=tracker.getIDforName(user);
		  }
		  
		  starts=tracker.getProgramIDs();
		  System.out.println(getUnusedCnt());
	}
	
	
	boolean[] used;
	int[][] graph;
	Set<Integer> starts;
	
	int getUnusedCnt(){
		
		int N=graph.length;
		int res=0;
		
		used=new boolean[N];
		for(int i=0;i<graph.length;i++){
			Arrays.fill(used, false);
			if(!isNeeded(i))
				res++;
		}
		
		return res;
	}
	
	boolean isNeeded(int i){
		used[i]=true;
		if(starts.contains(i))
			return true;
		
		for(int next:graph[i])
		 if(!used[next])
			 if(isNeeded(next))
				 return true;
		
		return false;
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
