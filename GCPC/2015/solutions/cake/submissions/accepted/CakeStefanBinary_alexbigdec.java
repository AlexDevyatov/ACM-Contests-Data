import java.util.Scanner;
import java.util.Locale;
import java.math.*;

/**
 * @author Stefan Toman (toman@tum.de)
 */
public class CakeStefanBinary_alexbigdec {
	public static MathContext mc = new MathContext(128);
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		sc.useLocale(Locale.US);

		// read input
		double a = sc.nextDouble();
		int n = sc.nextInt();

		Point[] vertices = new Point[n];
		for (int j = 0; j < n; j++) {
			int x = sc.nextInt();
			int y = sc.nextInt();
			vertices[j] = new Point(x, y);
		}
		
		BigDecimal min = BigDecimal.valueOf(2);
		BigDecimal max = BigDecimal.valueOf(1000);
		
		BigDecimal allowed_error = BigDecimal.valueOf(1e-6);
		while(max.subtract(min).compareTo(allowed_error) > 0) {
			BigDecimal mid = max.add(min).divide(BigDecimal.valueOf(2),mc);
			BigDecimal aTmp = cutAreaRatio(vertices, mid);
			if(aTmp.doubleValue() < 1-a) {
				max = mid;
			}
			else {
				min = mid;
			}
		}

		// output
		System.out.println((max.add(min).divide(BigDecimal.valueOf(2))));

		sc.close();
	}

	public static BigDecimal area(Point a, Point b, Point c) {
		BigDecimal bd = (a.x).multiply((b.y));
		bd = bd.add((a.y).multiply((c.x)));
		bd = bd.add((b.x).multiply((c.y)));
		bd = bd.subtract((a.x).multiply((c.y)));
		bd = bd.subtract((a.y).multiply((b.x)));
		bd = bd.subtract((b.y).multiply((c.x)));
		bd = bd.abs();
		bd = bd.divide(new BigDecimal("2", mc));
		return bd;
	}

	public static Point between(Point a, Point b, BigDecimal ratio) {
		return new Point(((ratio.subtract(BigDecimal.ONE)).multiply(a.x).add(b.x)).divide(ratio,mc),
							((ratio.subtract(BigDecimal.ONE)).multiply(a.y).add(b.y)).divide(ratio,mc));
	}

	static class Point {
		BigDecimal x, y;

		public Point(BigDecimal x, BigDecimal y) {
			super();
			this.x = (x);
			this.y = (y);
		}
		public Point(long x, long y) {
			super();
			this.x = BigDecimal.valueOf(x);
			this.y = BigDecimal.valueOf(y);
		}
	}

	public static BigDecimal vertexArea(Point[] vertices, BigDecimal s) {
		BigDecimal vertexArea = BigDecimal.valueOf(0);
		for (int j = 1; j <= vertices.length; j++) {
			vertexArea = vertexArea.add( area(
					between(vertices[j % vertices.length], vertices[j - 1], s),
					between(vertices[j % vertices.length], vertices[(j + 1)
							% vertices.length], s), vertices[j
							% vertices.length]));
		}
		return vertexArea;
	}
	
	public static BigDecimal cutAreaRatio(Point[] vertices, BigDecimal s) {
		BigDecimal area = BigDecimal.valueOf(0);
		for (int j = 1; j < vertices.length - 1; j++) {
			area = area.add( area(vertices[0], vertices[j], vertices[j + 1]));
		}
		
		return vertexArea(vertices, s).divide(area, mc);
	}
}
