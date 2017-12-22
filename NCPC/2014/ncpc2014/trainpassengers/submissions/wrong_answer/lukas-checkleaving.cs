//Solution by lukasP (Lukáš Poláček)
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

class Problem
{
    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);

        int[] x = reader.ReadLine().Split().Select(y => int.Parse(y)).ToArray();
        int c = x[0], n = x[1];

        bool ok = true;
        int cur = 0;
        foreach (int i in Enumerable.Range(0, n))
        {
            x = reader.ReadLine().Split().Select(y => int.Parse(y)).ToArray();
            cur += x[1] - x[0];

            if (x[2] > 0 && cur < c)
                ok = false;
            if (cur < 0 || cur > c)
                ok = false;
        }

        if (cur != 0)
            ok = false;

        Console.WriteLine(ok ? "possible" : "impossible");
    }
}
