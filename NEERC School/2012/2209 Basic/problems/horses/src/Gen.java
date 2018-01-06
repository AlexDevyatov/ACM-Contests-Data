import java.io.*;
import java.util.*;

public class Gen {

	static int done = 0;
	static ArrayList<Integer> data = new ArrayList<Integer>();

	static final Random rand = new Random(556668949239L);
	static final int maxai = (int)1e6;
	
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
		data.clear();
		out.println();
		out.close();
	}

	static void genSample1() throws IOException {
		data.add(1);
		data.add(2);
		data.add(4);
		data.add(8);
		
		print();
	}
	
	static void genSample2() throws IOException {
		data.add(1);
		data.add(1);
		data.add(1);
		
		print();
	}

	static void genSample3() throws IOException {
		data.add(1000000);
		
		print();
	}

	static void genSample4() throws IOException {
		data.add(1);
		data.add(2);
		data.add(4);
		data.add(5);
		
		print();
	}
	static void genSample5() throws IOException {
		data.add(1);
		data.add(1);
		data.add(4);
		data.add(8);
		data.add(11);
		data.add(13);
		
		print();
	}
	static void genSample6() throws IOException {
		data.add(1);
		data.add(2);
		data.add(5);
		data.add(5);
		data.add(11);
		data.add(13);
		
		print();
	}
	static void genRandom1(int length) throws IOException {
		int t = 1 + rand.nextInt(100);
		for (int i = 0; i < length; i++) {
			data.add(t);
			t += 1 + rand.nextInt(5);
		}
		
		print();
	}
	
	static void genRandom2(int length) throws IOException {
		int t = 1 + rand.nextInt(1000);
		for (int i = 0; i < length; i++) {
			data.add(t);
			t = Math.min(maxai, t + length - i + rand.nextInt(5));
		}
		
		print();
	}
	
	static void genRandom3(int length) throws IOException {
		int t = 1 + rand.nextInt(1000);
		int d = rand.nextInt(31) + 1;
		for (int i = 0; i < length; i++) {
			data.add(t);
			t = Math.min(maxai, t + 1 + (length - i) / d + rand.nextInt(d));
		}
		
		print();
	}
	
	public static void main(String[] args) throws IOException {
		File dir = new File("../tests");
		if (!dir.exists())
			dir.mkdir();
		done = 0;
		genSample1();
		genSample2();
		genSample3();
		genSample4();
		genSample5();
		genSample6();
		for (int i = 0; i < 5; i++) {
			genRandom1(1 + rand.nextInt(100));
		}
		for (int i = 0; i < 5; i++) {
			genRandom1(5000);
		}
		for (int i = 0; i < 2; i++) {
			genRandom2(4000 + rand.nextInt(1000));
		}
		for (int i = 0; i < 7; i++) {
			genRandom3(4000 + rand.nextInt(1000));
		}
		return;
	}
}
