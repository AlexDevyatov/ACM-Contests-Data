import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.*;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Set;
import java.util.TreeSet;

/*

Bottleneck: During the dynamical solution of the TSP, in every iteration all 
            possible subsets are tried, not only with states, which have the
	    right number of elements inside

*/

public class GreeceEgorSlow2 {

	
	public static void main(String[] args) throws Exception{
        new GreeceEgorSlow2().run();
    }

	
	private void run() throws Exception{
		Scanner sc = new Scanner(System.in);
		solveTestCase(sc);
	}
	
	
	void solveTestCase(Scanner sc) throws Exception{
		  int N= sc.nextInt();
		  int P= sc.nextInt();
		  int M= sc.nextInt();
		  int G= sc.nextInt();
		  int T= sc.nextInt();
		  
		  int additionalTime=0;
		  Set<Integer> placesToVisit=new TreeSet<Integer>();
		  placesToVisit.add(0);//start in Athen
		  for(int i=0;i<P;i++){
			  placesToVisit.add(sc.nextInt());
			  additionalTime+=sc.nextInt();
		  }
		  
		  List<int[]>[] graph=new List[N];
		  for(int i=0;i<N;i++)
			  graph[i]=new LinkedList<int[]>();
		  
		  for(int i=0;i<M;i++){
			  int from= sc.nextInt();
			  int to  = sc.nextInt();
			  int w   = sc.nextInt();
			  graph[from].add(new int[]{w,to});
			  graph[to].add(new int[]{w,from});
		  }
		 
		  int[][] dists=reduceGraph(graph, placesToVisit);
		  
		  
		  int[] times=runTSP(dists,T);
		  if(times[0]+additionalTime<=G)
			  System.out.println("possible without taxi");
		  else if(times[1]+additionalTime<=G)
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
	
	
	void capDistances(int[][] dists, int maxVal){
		for(int[] subar:dists)
			for(int i=0;i<subar.length;i++)
				subar[i]=Math.min(subar[i], maxVal);
	}
	
	
	void ini3DArrayWithMaxInt(int[][][] ar){
		for(int[][] subar:ar)
		  for(int[] subsubar:subar)	
			Arrays.fill(subsubar, Integer.MAX_VALUE);
	}
	
	int[] runTSP(int[][] dists, int taxiTime){
	   int n=dists.length;
	   if(n==1)
               return new int[]{0,0};
	   int MAX=1<<n;
	   int[][][] curBest=new int[2][n][MAX];
	   int[][][] nextBest=new int[2][n][MAX];

	   ini3DArrayWithMaxInt(curBest);
	   curBest[0][0][1]=0;//start in 0
	   
	   for(int j=1;j<n;j++){//number of visited sides
		 ini3DArrayWithMaxInt(nextBest);
		 for(int taxiUsed=0; taxiUsed<2;taxiUsed++)  
		   for(int curPos=0;curPos<n;curPos++)
			   for(int curState=0;curState<MAX;curState++){
				   if(curBest[taxiUsed][curPos][curState]==Integer.MAX_VALUE)
					   continue;
				   int curValue=curBest[taxiUsed][curPos][curState];
				   for(int i=0;i<n;i++){
					   if(i==curPos || dists[curPos][i]==Integer.MAX_VALUE)
						   continue;
					   int nextState=curState|(1<<i);
					   nextBest[taxiUsed][i][nextState]=Math.min(nextBest[taxiUsed][i][nextState], curValue+dists[curPos][i]);
					   if(taxiUsed==0)//we could take taxi
						   nextBest[1][i][nextState]=Math.min(nextBest[1][i][nextState], curValue+taxiTime);

				   }
		   }
		   int[][][] swapHelp=curBest;curBest=nextBest; nextBest=swapHelp;
	   }
	   
	   int[] res=new int[2];
	   Arrays.fill(res, Integer.MAX_VALUE);
	   
	   for(int taxi=0;taxi<2;taxi++)
		   for(int i=1;i<n;i++)
			   if(curBest[taxi][i][MAX-1]!=Integer.MAX_VALUE){
				   res[taxi]=Math.min(res[taxi], curBest[taxi][i][MAX-1]+dists[i][0]);
				   if(taxi==0)
					   res[1]=Math.min(res[1], curBest[0][i][MAX-1]+taxiTime);//last ride with taxi
			   }
	   return res;
	}

}

