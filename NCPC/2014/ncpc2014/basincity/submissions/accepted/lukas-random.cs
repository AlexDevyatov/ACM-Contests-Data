//Solution by lukasP (Lukáš Poláček)
//Random solution. Surprisingly only 3^k iterations are provably enough. On our testdata 30 000 is
//good enough.
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

class Problem
{
    static List<bool> seen;
    static List<List<int>> g;
    static int n, d;
    static Random rnd;

    static bool go()
    {
        int cnt = n;
        for (int j = 0; j < d; j++)
        {
            if (cnt == 0)
                return false;

            int r = Enumerable.Range(0, n).Where(x => !seen[x]).Skip(rnd.Next(cnt)).First();
            seen[r] = true;
            cnt--;
            foreach (int i in g[r])
                if (!seen[i])
                {
                    seen[i] = true;
                    cnt--;
                }
        }

        return true;
    }

    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);
        d = int.Parse(reader.ReadLine());
        n = int.Parse(reader.ReadLine());

        if (d * 5 - 4 <= n)
        {
            Console.WriteLine("possible");
            return;
        }

        g = Enumerable.Range(0, n).Select(x => new List<int> ()).ToList();
        foreach (int i in Enumerable.Range(0, n))
            g[i] = reader.ReadLine().Split().Select(x => int.Parse(x) - 1).Skip(1).ToList();

        bool ok = false;
        rnd = new Random();
        for (int iter = 0; iter < 35000 && !ok; iter++)
        {
            seen = Enumerable.Repeat(false, n).ToList();
            if (go()) ok = true;
        }

        Console.WriteLine(ok ? "possible" : "impossible");
    }
}
