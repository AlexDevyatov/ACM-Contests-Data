// auteur: Nicky Gerritsen

// d<n eventueel interessante case

using System.Collections;

public class BadWiring_Solution
{
    static int inf=20112012;

    static int n,d;
    static int[] q;
    
    static int bitcount(int a)
    {
        int res=0;
        for(;a>0;a/=2)
            res+=a&1;
        return res;
    }

    static int check(int z, int len)
    {
        int res=0;
        int[] a=new int[n];
        for(int i=0;i<n;i++)
            a[i]=q[i];
        for(int i=0;i<len;i++) if((z&(1<<i))!=0)
        {
            res++;
            for(int j=-d;j<=d;j++)
                if(i+j>=0&&i+j<n)
                    a[i+j]^=1;
        }
        for(int i=0;i<n;i++) if(a[i]==1)
        {
            res++;
            if(i+d>=n)
                return inf;
            for(int j=0;j<=d+d;j++)
                if(i+j<n)
                    a[i+j]^=1;
        }
        return res;
    }

    static void solve()
    {
        int best=inf;
        int brutelen=System.Math.Min(d,n);
        for(int i=0;i<(1<<brutelen);i++)
            best=System.Math.Min(best,check(i,brutelen));
		
		if (best == inf) {
			System.Console.WriteLine("impossible");
		} else {
			System.Console.WriteLine(best);
		}
    }
    
    static void notvalid(string s)
    {
        System.Console.WriteLine(s);
    }

    public static void Main()
    {
        //Scanner sc=new Scanner(new File("in2.txt"));

        int numruns=int.Parse(System.Console.ReadLine());
        for(int run=1;run<=numruns;run++)
        {
			string[] line = System.Console.ReadLine().Split();
            n=int.Parse(line[0]);
            d=int.Parse(line[1]);

            q=new int[n];
			line = System.Console.ReadLine().Split();
            for(int i=0;i<n;i++) {
                q[i]=int.Parse(line[i]);
			}

            // testcase validation
            if(n<1||n>100)
                notvalid("n out of bounds: "+n);
            if(d<0||d>15)
                notvalid("d out of bounds: "+d);
            for(int i=0;i<n;i++)
                if(q[i]!=0&&q[i]!=1)
                    notvalid("q["+i+"] out of bounds: "+q[i]);

            solve();
        }
    }
}