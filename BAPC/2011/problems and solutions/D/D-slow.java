// auteur: Misha Stassen
// Brute Force oplossing om correctheid te checken

// d<n eventueel interessante case

import java.io.*;
import java.util.*;

public class BadWiring_Brute
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

    static int check(int z)
    {
        int res=0;
        int[] a=new int[n];
        for(int i=0;i<n;i++)
            a[i]=q[i];
        for(int i=0;i<n;i++) if((z&(1<<i))!=0)
        {
            res++;
            for(int j=-d;j<=d;j++)
                if(i+j>=0&&i+j<n)
                    a[i+j]^=1;
        }
        for(int i=0;i<n;i++)
            if(a[i]!=0)
                return inf;

        return res;
    }

    static void solve()
    {
        int best=inf;
        for(int i=0;i<(1<<n);i++)
            best=Math.min(best,check(i));

        System.out.println(best==inf?"impossible":best);
    }

    public static void main(String[] args) throws IOException
    {
        //Scanner sc=new Scanner(new File("in.txt"));
        Scanner sc=new Scanner(System.in);
        
        int numruns=sc.nextInt();
        for(int run=1;run<=numruns;run++)
        {
            n=sc.nextInt();
            d=sc.nextInt();
            q=new int[n];
            for(int i=0;i<n;i++)
                q[i]=sc.nextInt();
            solve();
        }
    }
}
