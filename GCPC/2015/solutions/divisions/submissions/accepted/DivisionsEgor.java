import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.BigInteger;


public class DivisionsEgor {
	public static void main(String[] args)throws Exception{
        new DivisionsEgor().run();
    }
	
	private void run() throws Exception{
		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
		  long N=Long.parseLong(reader.readLine());
		  System.out.println(getDivisorCnt(N));	  
		  reader.close();
	}
	
    boolean isQuadrat(long N){
    	double d=Math.sqrt(N);
    	
    	long start=(long)Math.ceil(d-10);
    	long end=(long)Math.ceil(d+10);
    	for(long i=start;i<=end;i++)
    		if(i*i==N)
    			return true;
    	return false;
    }
	
	long getDivisorCnt(long N){
		long res=1;
		for(long i=2;i<=1_000_000;++i){
			long cnt=1;
			while(N%i==0){
				N/=i;
				cnt++;
			}
			res*=cnt;
		}
		
		if(N==1)
			return res;
		
		//there is still something there, but we know: this one is prime or has two factors
		if(isPrim(N))
			return res*2L;
		else{//is not prime, but we know there are at most two factors
			if(isQuadrat(N))//the factors are the same:
				return res*3L;
			else//factors are different
				return res*4L;
		}
	}
	
	boolean isPrim(long N){
		BigInteger bi=BigInteger.valueOf(N);
		return bi.isProbablePrime(100);
	}
}
