//Solution by lukasP (Lukáš Poláček)
//Rolling hash
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

class Problem
{
    static int mod = 326932427;
    static long po = 41351;
    static int cyc = 360000;
    static StreamReader reader;

    static int read_normalize(int n)
    {
        List<int> x = reader.ReadLine().Split().Select(z => int.Parse(z)).
            OrderBy(z => z).ToList();
        List<int> y = new List<int> ();

        int hash = 0;
        long big = 1;
        for (int i = 0; i < n; i++)
        {
            y.Add((x[(i + 1) % n] - x[i] + cyc) % cyc);
            hash = (int)((hash * po + y[i]) % mod);
            big = (int)(big * po % mod);
        }

        big = (mod + 1 - big) % mod;
        int res = hash;
        for (int i = 0; i < n; i++)
        {
            hash = (int)((hash * po + big * y[i]) % mod);
            res = Math.Min(res, hash);
        }
        return res;
    }

    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        reader = new StreamReader(bs);

        int n = int.Parse(reader.ReadLine());
        int a = read_normalize(n);
        int b = read_normalize(n);
        Console.WriteLine((a == b) ? "possible" : "impossible");
    }
}
