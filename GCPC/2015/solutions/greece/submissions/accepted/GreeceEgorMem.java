import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Set;
import java.util.TreeSet;

/*

using memoization for calculation of TSP. The advantage of this is that only states
that are really needed are touched.
 
*/

public class GreeceEgorMem {

	
	public static void main(String[] args) throws Exception{
        new GreeceEgorMem().run();
    }

	
	private void run() throws Exception{
		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
			  solveTestCase(reader);
	}
	
	
	void solveTestCase(BufferedReader reader) throws Exception{
		  String[] npmgt=reader.readLine().split(" ");
		  int N=Integer.parseInt(npmgt[0]);
		  int P=Integer.parseInt(npmgt[1]);
		  int M=Integer.parseInt(npmgt[2]);
		  int G=Integer.parseInt(npmgt[3]);
		  int T=Integer.parseInt(npmgt[4]);
		  
		  int additionalTime=0;
		  Set<Integer> placesToVisit=new TreeSet<Integer>();
		  placesToVisit.add(0);//start in Athen
		  for(int i=0;i<P;i++){
			  String[] place=reader.readLine().split(" ");
			  placesToVisit.add(Integer.parseInt(place[0]));
			  additionalTime+=Integer.parseInt(place[1]);
		  }
		  
		  List<int[]>[] graph=new List[N];
		  for(int i=0;i<N;i++)
			  graph[i]=new LinkedList<int[]>();
		  
		  for(int i=0;i<M;i++){
			  String[] edge=reader.readLine().split(" ");
			  int from=Integer.parseInt(edge[0]);
			  int to=Integer.parseInt(edge[1]);
			  int w=Integer.parseInt(edge[2]);
			  graph[from].add(new int[]{w,to});
			  graph[to].add(new int[]{w,from});
		  }
		 
		  int[][] dists=reduceGraph(graph, placesToVisit);
		  
		  TSPSolver tspSolver=new TSPSolver(dists, T);
		  if(tspSolver.getBest(0, 0, tspSolver.MAX-1)+additionalTime<=G)
			  System.out.println("possible without taxi");
		  else if(tspSolver.getBest(1, 0, tspSolver.MAX-1)+additionalTime<=G)
			  System.out.println("possible with taxi");
		  else
			  System.out.println("impossible"); 
			  
	}
	
	
	int[][] reduceGraph(List<int[]>[] graph, Set<Integer> places){
		int n=places.size();
		int[][] result=new int[n][n];
		int ind1=0;
		for(int start:places){
			int[] dists=dijkstra(graph, start);
			int ind2=0;
			for(int end:places)
				result[ind1][ind2++]=dists[end];
			
			ind1++;
		}
		return result;
	}
	
	
	int[] dijkstra(List<int[]>[] graph, int start){
		  int N=graph.length;
		  int[] dists=new int[N];
		  Arrays.fill(dists,Integer.MAX_VALUE);
		  //int[0] - weight -> other information int[1]...int[?]
		  Queue<int[]> q=new PriorityQueue<int[]>(11,new Comparator<int[]>(){
			  public int compare(int[] a, int[] b){
				  if(a[0]<b[0]) return -1;
				  if(a[0]==b[0]) return 0;
				  return 1;
			  }
		  });
		  //costs[0][0]=0;
		  q.offer(new int[]{0, start});
		  dists[start]=0;
		  while(! q.isEmpty()){
			  int[] akt=q.poll();
			  int current=akt[1];
			  int curDist=akt[0];
			  if(curDist!=dists[current]) continue; //already processed
			  for(int[] edge:graph[current]){
				  	   int next=edge[1];
			    	   int nextDist=dists[current]+edge[0];
			    	   if(dists[next]>nextDist){
			    		   dists[next]=nextDist;
				    	   q.add(new int[]{nextDist, next});
			    	   }  
		      }
		  }	
		  return dists;
	}
	
	
	

	
  public class TSPSolver{
	  int[][][] curBest;
      int n;
      int[][] dists;
      int taxiTime;
      int MAX;
      
  	   private void ini3DArrayWithMaxInt(int[][][] ar){
		for(int[][] subar:ar)
		  for(int[] subsubar:subar)	
			Arrays.fill(subsubar, -1);
  	    }
      
      TSPSolver(int[][] dists, int taxiTime){
    	  this.dists=dists;
    	  this.taxiTime=taxiTime;
    	  n=dists.length;
   	      MAX=1<<n;
   	      curBest=new int[2][n][MAX];
   	      ini3DArrayWithMaxInt(curBest);
   	      for(int i=0;i<n;i++){
   	    	 curBest[0][i][1<<i]=dists[0][i];//start in 0
   	    	 curBest[1][i][1<<i]=taxiTime;
   	      }
      }
	  
      int getBest(int taxiTaken, int position, int state){
    	 if(curBest[taxiTaken][position][state]==-1){
    		 int res=Integer.MAX_VALUE;
    		 int oldState=state^(1<<position);
  			 for(int i=0;i<n;i++)
  				if( dists[position][i]!=Integer.MAX_VALUE && ((1<<i) & oldState)!=0){
  					int val= getBest(taxiTaken, i, oldState);
  					if(val!=Integer.MAX_VALUE)
  						res=Math.min(res,val+dists[position][i]);
  					if(taxiTaken==1){
  						val=getBest(0, i, oldState);
  						if(val!=Integer.MAX_VALUE)
  							res=Math.min(res, val+taxiTime);
  					}
  				}
  			curBest[taxiTaken][position][state]=res;
  		}
  		return curBest[taxiTaken][position][state];
      }
  }

}


