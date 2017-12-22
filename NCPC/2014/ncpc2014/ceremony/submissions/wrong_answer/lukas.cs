//Solution by lukasP (Lukáš Poláček)
//Wrong initialisation of res
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
        int n = int.Parse(reader.ReadLine());

        List<int> x = reader.ReadLine().Split().Select(y => int.Parse(y)).OrderBy(y => y).ToList();
        int res = x.Last();
        foreach (int i in Enumerable.Range(0, n))
            res = Math.Min(res, x[i] + (n - i - 1));
        Console.WriteLine(res);
    }
}
