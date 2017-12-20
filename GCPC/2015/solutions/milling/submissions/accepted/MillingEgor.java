import java.io.BufferedReader;
import java.io.InputStreamReader;

/*
* Output is the bottleneck here -> use  StringBuilder
*/

public class MillingEgor {
	public static void main(String[] args)throws Exception{
        new MillingEgor().run();
    }
	
	int[] readArrayFromLine(String line){
		String[] zahlen=line.split(" ");
		int[] res = new int[zahlen.length];
		for(int i=0;i<zahlen.length;i++)
			res[i]=Integer.parseInt(zahlen[i]);
		
		return res;
	}
	
	void max(int[] output, int[] other){
		int size=Math.max(output.length, other.length);//crash for diff sizes
		for(int i=0;i<size;i++)
			output[i]=Math.max(output[i], other[i]);
	}
	
	void min(int[] output, int[] other){
		int size=Math.max(output.length, other.length);//crash for diff sizes
		for(int i=0;i<size;i++)
			output[i]=Math.min(output[i], other[i]);		
	}
	
	void invert(int[] output, int Y){
		int size=output.length;
		for(int i=0;i<size;i++)
			output[i]=Y-output[i];
	}
	
	void cout(int[] ar, StringBuilder builder){
		int cnt=0;
		for(int i:ar){
			builder.append(i);
			if(cnt!=ar.length)
				builder.append(' ');
			cnt++;
		}
		builder.append('\n');
	}


	private void run() throws Exception{
		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
		  
		  String[] ws=reader.readLine().split(" ");
		  int W=Integer.parseInt(ws[0]);
		  int S=Integer.parseInt(ws[1]);
		  String[] xy=reader.readLine().split(" ");
		  
		  
		  int X=Integer.parseInt(xy[0]);
		  int Y=Integer.parseInt(xy[1]);
		  
		  int[][] Ws= new int[W][];
		  for(int i=0;i<W;i++)
			  Ws[i]=readArrayFromLine(reader.readLine());
		  
		  int[] program=new int[X];
		  for(int i=0;i<S;i++)
			  max(program, readArrayFromLine(reader.readLine()));
		  
		  invert(program, Y);
		  StringBuilder builder=new StringBuilder(4*W*X);
		  
		  for(int i=0;i<W;i++){
			  min(Ws[i], program);
			  cout(Ws[i], builder);
		  }
		  
		  System.out.println(builder);
	}
}

