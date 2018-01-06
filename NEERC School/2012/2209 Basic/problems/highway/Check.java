import ru.ifmo.testlib.*;
import ru.ifmo.testlib.Outcome.Type;

public class Check implements Checker {

	@Override
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		String pans = ouf.nextToken();
		String jans = ans.nextToken();
		double jt = 0, pt = 0;
		int W = inf.nextInt();
		int H = inf.nextInt();
		int n = inf.nextInt();
		
		if (pans.equals("Yes")) {
			pt = ouf.nextDouble();
			if ((pt < 0) || (pt > W)) {
				throw new Outcome(Type.WA, "Contestant's answer is definitely wrong"); 
			}
		}
		
		if (jans.equals("Yes")) {
			jt = ans.nextDouble();
			if ((jt < 0) || (jt > W)) {
				throw new Outcome(Type.FAIL, "Jury's answer is definitely wrong"); 
			}
		}
		
		
		for (int i = 0; i < n; i++) {
			int x1 = inf.nextInt();
			int y1 = inf.nextInt();
			int x2 = inf.nextInt();
			int y2 = inf.nextInt();
			
			if (x1 > x2) {
				int tmp = x1;
				x1 = x2;
				x2 = tmp;
			}
			
			if (y1 > y2) {
				int tmp = y1;
				y1 = y2;
				y2 = tmp;
			}
			
			if (jans.equals("Yes")) {
				double nx1 = x1 + jt + y1 % W;
				double nx2 = x2 + jt + y1 % W;
				//System.err.println(nx1 + " " + nx2);
				
				while (nx1 >= W - 1e-7) {
					nx1 -= W;
					nx2 -= W;
				}
				
				//System.err.println(nx1 + " " + nx2);
				
				//System.err.println(nx2 + " " + (nx1 + y2 - y1));
				//System.err.println(nx2 + " " + (nx2 + y2 - y1));
				if ((nx2 > W + 1e-7) && (nx1 < W-1e-7)) {
				    System.err.println(nx1 + " " + nx2);
					return new Outcome(Type.FAIL, "Jury's man was killed by car number " + (i + 1));
				}
				if ((nx1 + (y2 - y1) > W + 1e-7) && (nx1 < W + 1e-7)) {
				    System.err.println(nx1 + " " + (nx1 + y2 - y1));
					return new Outcome(Type.FAIL, "Jury's man was killed by car number " + (i + 1));
				}
				if ((nx2 + (y2 - y1) > W + 1e-7) && (nx2 < W + 1e-7)) {
				    System.err.println(nx2 + " " + (nx2 + y2 - y1));
					return new Outcome(Type.FAIL, "Jury's man was killed by car number " + (i + 1));
				}
			}
			
			if (pans.equals("Yes")) {
				double nx1 = x1 + pt + y1 % W;
				double nx2 = x2 + pt + y1 % W;
				
				while (nx1 > W - 1e-7) {
					nx1 -= W;
					nx2 -= W;
				}
				if ((nx2 > W + 1e-7) && (nx1 < W-1e-7))
					return new Outcome(Type.WA, "Participant's man was killed by car number " + (i + 1));
				if ((nx1 + (y2 - y1) > W + 1e-7) && (nx1 < W + 1e-7)) {
					return new Outcome(Type.WA, "Participant's man was killed by car number " + (i + 1));
				}
				if ((nx2 + (y2 - y1) > W + 1e-7) && (nx2 < W + 1e-7)) {
					return new Outcome(Type.WA, "Participant's man was killed by car number " + (i + 1));
				}
			}
		}
		System.err.println(jans + " " + pans);
		if (jans.equals(pans))
			return new Outcome(Type.OK, "Ok");
		if (pans.equals("Yes"))
			return new Outcome(Type.FAIL, "Panic");
		return new Outcome(Type.WA, "Answer was now found");
	}

}
