import java.io.*;
import java.util.*;

public class highway_pk {

	PrintWriter out;
	BufferedReader br;
	StringTokenizer st;

	String nextToken() throws IOException {
		while ((st == null) || (!st.hasMoreTokens()))
			st = new StringTokenizer(br.readLine());
		return st.nextToken();
	}

	public int nextInt() throws IOException {
		return Integer.parseInt(nextToken());
	}

	public long nextLong() throws IOException {
		return Long.parseLong(nextToken());
	}

	public double nextDouble() throws IOException {
		return Double.parseDouble(nextToken());
	}

	class Event implements Comparable<Event> {
		int x, type;

		@Override
		public int compareTo(Event arg0) {
			if (x != arg0.x)
				return x - arg0.x;
			return type - arg0.type;
		}

		public Event(int x, int type) {
			super();
			this.x = x;
			this.type = type;
		}

	}

	public void solve() throws IOException {
		int w = nextInt();
		int h = nextInt();
		int n = nextInt();
		ArrayList<Event> events = new ArrayList<highway_pk.Event>();
		for (int i = 0; i < n; i++) {
			int x1 = nextInt();
			int y1 = nextInt();
			int x2 = nextInt();
			int y2 = nextInt();
			add(events, Math.min(x1, x2) + Math.min(y1, y2), Math.max(x1, x2)
					+ Math.max(y1, y2), w);
		}
		Collections.sort(events);
		int cnt = 0;
		int answer = -1;
		for (Event x : events) {
			cnt += x.type;
			if (cnt > 0)
				continue;
			else
				if ((x.x >= 0) && (x.x <= w))
					answer = w - x.x;
		}
		if (answer == -1)
			out.println("No");
		else {
			out.println("Yes");
			out.println(answer);
		}

	}

	private void add(ArrayList<Event> events, int x1, int x2, int W) {
		x2 -= (x1 / W) * W;
		x1 %= W;
		events.add(new Event(x1, 1));
		if (x2 > W) {
			events.add(new Event(-1, +1));
			events.add(new Event(x2 - W, -1));
		} else {
			events.add(new Event(x2, -1));
		}
	}

	public void run() {
		try {
			br = new BufferedReader(new InputStreamReader(System.in));
			out = new PrintWriter(System.out);

			br = new BufferedReader(new FileReader("highway.in"));
			out = new PrintWriter("highway.out");

			solve();

			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		new highway_pk().run();
	}
}
