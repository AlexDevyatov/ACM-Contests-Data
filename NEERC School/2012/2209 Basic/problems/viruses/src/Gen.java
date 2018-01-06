import java.io.*;
import java.util.*;

public class Gen {

	static int done = 0;
	static ArrayList<Integer> data = new ArrayList<Integer>();

	static final Random rand = new Random(556668949239L);
	static final int maxai = (int)1e9;
	static final int maxn = 5000;
	
	static void print() throws IOException {
		done++;
		System.err.println(done);
		PrintWriter out;
		if (done < 10)
			out = new PrintWriter("../tests/0" + String.valueOf(done));
		else
			out = new PrintWriter("../tests/" + String.valueOf(done));

		out.println(data.size());
		for (int i = 0; i < data.size(); i++) {
			if (i < data.size() - 1)
			out.print(data.get(i) + " ");
			else
			out.print(data.get(i));
		}
		out.println();
		data.clear();
		out.close();
	}

	static void genRandomHeap(int len) throws IOException {
		int k = 1 + rand.nextInt(len - 1);
		int[] a = new int[len];
		a[0] = rand.nextInt(1000);
		for (int i = 1; i < len; i++) {
			a[i] = Math.min(maxai - 1, a[(i - 1) / k] + rand.nextInt(12345));
		}
		
		for (int i = 0; i < len; i++) {
			data.add(maxai - a[i]);
		}
		
		print();
	}	
	
	static void genRandomHeap2(int len) throws IOException {
		for (int i = 0; i < len; i++) {
			data.add(1 + rand.nextInt(maxai));
		}
		
		print();
	}
	
	static void genRandomHeap3(int len) throws IOException {
		int k = len - 1;
		int[] a = new int[len];
		a[0] = rand.nextInt(1000);
		for (int i = 1; i < len; i++) {
			a[i] = Math.min(maxai - 1, a[(i - 1) / k] + rand.nextInt(12345));
		}
		
		for (int i = 0; i < len; i++) {
			data.add(maxai - a[i]);
		}
		
		print();
	}

	
	static void genSample1() throws IOException {
		for (int i = 1; i <= 5; i++) {
			data.add(i);
		}
		
		print();
	}
	
	static void genSample2() throws IOException {
		data.add(5);
		data.add(4);
		data.add(2);
		data.add(3);
		data.add(1);
		
		print();
	}
	
	public static void main(String[] args) throws IOException {
		File dir = new File("../tests");
		if (!dir.exists())
			dir.mkdir();
		done = 0;
		genSample1();
		genSample2();
		for (int i = 0; i < 20; i++) {
			genRandomHeap(1 + rand.nextInt(100));
		}
		for (int i = 0; i < 7; i++) {
			genRandomHeap(4000 + rand.nextInt(1000));
		}
		for (int i = 0; i < 7; i++) {
			genRandomHeap2(4000 + rand.nextInt(1000));
		}
		for (int i = 0; i < 3; i++) {
			genRandomHeap3(4000 + rand.nextInt(1000));
		}
		return;
	}
}
