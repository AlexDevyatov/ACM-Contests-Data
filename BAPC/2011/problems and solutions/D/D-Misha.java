// auteur: Misha Stassen

// d<n eventueel interessante case

import java.io.*;
import java.util.*;

public class BadWiring_Solution
{
    static final int inf=20112012;

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
        int brutelen=Math.min(d,n);
        for(int i=0;i<(1<<brutelen);i++)
            best=Math.min(best,check(i,brutelen));

        System.out.println(best==inf?"impossible":best);
    }
    
    static void notvalid(String s)
    {
        System.out.println(s);
        System.exit(0);
    }

    public static void main(String[] args) throws IOException
    {
        //Scanner sc=new Scanner(new File("in2.txt"));
        Scanner sc=new Scanner(System.in);

        int numruns=sc.nextInt();
        for(int run=1;run<=numruns;run++)
        {
            n=sc.nextInt();
            d=sc.nextInt();

            q=new int[n];
            for(int i=0;i<n;i++)
                q[i]=sc.nextInt();

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