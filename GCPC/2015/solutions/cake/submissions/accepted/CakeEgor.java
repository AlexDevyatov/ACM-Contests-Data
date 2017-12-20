import java.io.BufferedReader;
import java.io.InputStreamReader;

/*
 *  calculates the maximal possible area cut off (for s=2) and scales it so, the needed area cut off is reached
 *  tries to use integer data types as long as possible
 */
public class CakeEgor {
	
	public static void main(String[] args) throws Exception{
        new CakeEgor().run();
    }

	
	private void run() throws Exception{
		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
		  String[] an=reader.readLine().split(" ");
		  double a=Double.parseDouble(an[0]);
		  int N=Integer.parseInt(an[1]);
		  
		  int[][] points=new int[N][];
		  for(int i=0;i<N;i++){
			  String[] coords=reader.readLine().split(" ");
			  points[i]=new int[]{Integer.parseInt(coords[0])*2, Integer.parseInt(coords[1])*2};//x2, thus middle point of the edges are integer
		  }
		  
		  long wholeArea=getConvexArea(points);
		  long maxCuttedArea=getCuttedArea(points);
		  
		  double maxCuttedAreaRelative=(double)maxCuttedArea/(double)wholeArea;
		  double scaleFactor=Math.sqrt((1.0-a)/maxCuttedAreaRelative);
		  
		  
		  System.out.println(2.0/scaleFactor);
		  
	}
	
	long getTriangleArea(int[] p1, int[] p2, int[] p3){//factor 0.5 is omitted
		long dx1=p2[0]-p1[0];
		long dy1=p2[1]-p1[1];
		
		long dx2=p3[0]-p1[0];
		long dy2=p3[1]-p1[1];
		
		return Math.abs(dx1*dy2-dx2*dy1);
	}
	
	
	long getConvexArea(int[][] points){
		long res=0;
		
		for(int i=2;i<points.length;i++)
			res+=getTriangleArea(points[0], points[i-1], points[i]);
		
		return res;
	}
	
	int[] getMiddle(int[][] points, int a, int b){
		return new int[]{(points[a][0]+points[b][0])/2,
				         (points[a][1]+points[b][1])/2};
	}
	
	long getCuttedArea(int[][] points){
		long res=0;
		int n=points.length;
		for(int i=0;i<n;i++){
			int left=(i+1)%n;
			int right=(i+n-1)%n;
			
			int[] p2=getMiddle(points, i, left);
			int[] p3=getMiddle(points, i, right);
			
			res+=getTriangleArea(points[i], p2, p3);
		}
		
		return res;
	}
}

