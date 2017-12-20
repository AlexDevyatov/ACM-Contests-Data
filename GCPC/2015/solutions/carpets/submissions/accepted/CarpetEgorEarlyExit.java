import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Comparator;

/*

Sanity check first, whether there is a solution possible.

Than brute force/exhaustive search approach: find the first empty cell, try to put one of the vacant carpets 

 Uses a boolean field for looking up, whether a carpet can be placed
*/

public class CarpetEgorEarlyExit {
	public static void main(String[] args)throws Exception{
        new CarpetEgorEarlyExit().run();
    }
	
	boolean[] used;
	int[][] carpets;
	boolean[][] floor;
	
	
	boolean canReachArea(int[][] carpets, boolean[] used, int Area){
		boolean[] reached=new boolean[Area+1];
		reached[0]=true;
		for(int i=0;i<used.length;i++){
			if(used[i])
				continue;
			for(int j=Area; j>=0;j--){
				if(reached[j]){
					int step=carpets[i][0]*carpets[i][1];
					if(j+step<=Area)
						reached[j+step]=true;
				}
			}
		}
		return reached[Area];
	}
	
	
	boolean canReachLength(int[][] carpets, boolean[] used, int Length){
		boolean[] reached=new boolean[Length+1];
		reached[0]=true;
		for(int i=0;i<used.length;i++){
			if(used[i])
				continue;
			for(int j=Length; j>=0;j--){
				if(reached[j]){
					int step=carpets[i][0];
					if(j+step<=Length)
						reached[j+step]=true;
					step=carpets[i][1];
					if(j+step<=Length)
						reached[j+step]=true;
				}
			}
		}
		return reached[Length];
	}
	
	
	boolean canPut(int x, int y, int xDim, int yDim){
		int endX=x+xDim;
		int endY=y+yDim;
		if(endX>floor.length || endY>floor[0].length)
			return false;
		for(int i=x;i<endX;i++)
			for(int j=y;j<endY;j++)
				if(floor[i][j])
					return false;

		return true;
	}
	
	void doPut(int x, int y, int xDim, int yDim, boolean value){
		int endX=x+xDim;
		int endY=y+yDim;
		for(int i=x;i<endX;i++)
			for(int j=y;j<endY;j++)
				floor[i][j]=value;
	}
	
	int[] findFirst(){
		for(int x=0;x<floor.length;x++)
			for(int y=0;y<floor[x].length;y++)
				if(!floor[x][y])
					return new int[]{x,y};
		return null;
	}
	
boolean exploreCarpet(int x, int y, int xD, int yD){
	boolean result=false;
	if(canPut(x, y, xD, yD)){
		doPut(x, y, xD, yD, true);
		result=backTrack();
		doPut(x, y, xD, yD, false);
	}
	return result;
}
	
boolean backTrack(){
	int[] xy=findFirst();
	//System.out.println();
	//System.out.println(Arrays.deepToString(floor));
	//System.out.println(Arrays.toString(xy));
	if(xy==null)
		return true;
	
	int n=used.length;
	
	for(int i=0;i<n;i++){
		if(!used[i]){
			used[i]=true;
			if(exploreCarpet(xy[0],xy[1],carpets[i][0], carpets[i][1]))
				return true;
			if(exploreCarpet(xy[0],xy[1],carpets[i][1], carpets[i][0]))
				return true;
			used[i]=false;
		}
	}
	
	return false;
}
	

	private void run() throws Exception{
		 carpets=new int[8][];  
		
		 BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
		  
		  String[] wh=reader.readLine().split(" ");
		  int W=Integer.parseInt(wh[0]);
		  int H=Integer.parseInt(wh[1]);
		  
		  floor=new boolean[W][H];
		  
		  int c=Integer.parseInt(reader.readLine());
		  int cnt=0;
		  for(int i=0;i<c;i++){
			  String[] nwh=reader.readLine().split(" ");
			  int n=Integer.parseInt(nwh[0]);
			  
			  int w=Integer.parseInt(nwh[1]);
			  int h=Integer.parseInt(nwh[2]);
			  
			  for(int k=0;k<n;k++){
				  carpets[cnt++]=new int[]{w,h};
			  }
		  }
		  
		  //heuristic: big areas first (is not really better)
		  //Arrays.sort(carpets, 0, cnt, new Comparator<int[]>(){
		  //	  public int compare(int[] a, int[] b){
		  //		  return -a[0]*a[1]+b[0]*b[1];
		  //	  }});
		  used=new boolean[cnt];
		  
		  if(!canReachArea(carpets, used, H*W) || !canReachLength(carpets, used, W) || !canReachLength(carpets, used, H)){
			  System.out.println("no");
			  return;
		  }
			  
		  if(backTrack())
			  System.out.println("yes");
		  else
			  System.out.println("no");
	}
}

