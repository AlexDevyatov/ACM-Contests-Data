import java.io.*;
import java.util.*;

public class Gen {

	static int done = 0;
	static ArrayList<String> data = new ArrayList<String>();

	static final Random rand = new Random(556668949239L);

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
			out.println(data.get(i));
		}
		data.clear();
		out.close();
	}

	static void genSimple() throws IOException {
		data.add("2:1");
		data.add("0:9");
		data.add("1:1");
		print();
	}

	static void genAll() throws IOException {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				data.add(i + ":" + j);
			}
		}
		Collections.shuffle(data, rand);
        print();
	}

	public static void main(String[] args) throws IOException {
		File dir = new File("../tests");
		if (!dir.exists())
			dir.mkdir();
		done = 0;
		genSimple();
		genAll();
		return;
	}
}
