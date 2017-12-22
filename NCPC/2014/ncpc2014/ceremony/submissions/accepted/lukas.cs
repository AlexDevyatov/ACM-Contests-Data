//Solution by lukasP (Lukáš Poláček)
//Sorting + greedy
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
        int res = Enumerable.Range(0, n).Min(z => x[z] + (n - z - 1));
        Console.WriteLine(Math.Min(n, res));
    }
}
