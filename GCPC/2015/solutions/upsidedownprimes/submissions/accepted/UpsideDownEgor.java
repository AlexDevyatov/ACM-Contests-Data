import java.io.BufferedReader;
import java.io.InputStreamReader;


public class UpsideDownEgor {
	
	public static void main(String[] args) throws Exception{
        new UpsideDownEgor().run();
    }

	
	private void run() throws Exception{
		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
		  String prime=reader.readLine();
		  
		  if(!isPrime(Long.parseLong(prime))){
			  System.out.println("no");
			  return;
		  }
		  
		  Long upsideDown=Long.parseLong(makeUpsideDown(prime));
		  
		  if(isPrime(upsideDown))
			  System.out.println("yes");
		  else
			  System.out.println("no");
		  
	}
	
	boolean smallIsPrime(long z){
		if(z==1L)
			return false;
		for(long i=2L;i<z-1L;i++)
			if(z%i==0L)
				return false;
		
		return true;
	}
	
	boolean isPrime(long z){
		//System.out.println("number: "+z);
		if(z<1000L)
			return smallIsPrime(z);
		long end=(long)Math.ceil(Math.sqrt(z))+100L;
		
		//unroll_2:
		if(z%2L==0L)
			return false;
		//unroll_3
		if(z%3L==0L)
			return false;

		//unroll_5
		if(z%5L==0L)
			return false;		
		
		long[] kk={4L,2L,4L,2L,4L,6L,2L,6L};
		
		for(long i=7L;i<=end;){
			for(long d:kk){
				if(z%i==0L)
					return false;
				i+=d;
			}
		}
		
		return true;
	}
	
	String makeUpsideDown(String prime){
		String res="";
		for(int i=0;i<prime.length();i++){
			char ch=prime.charAt(i);
			switch(ch){
				case '0': res='0'+res; break;
				case '1': res='1'+res; break;
				case '2': res='2'+res; break;
				case '3': return "1";
				case '4': return "1";
				case '5': res='5'+res; break;
				case '6': res='9'+res; break;
				case '7': return "1";
				case '8': res='8'+res; break;
				case '9': res='6'+res; break;
				default:
					return "1";
			}		
		}
		return res;
	}
}

