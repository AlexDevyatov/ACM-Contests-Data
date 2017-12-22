//Solution by lukasP (Lukáš Poláček)
//Just compare the expected values
using System;
using System.Collections.Generic;
using System.Linq;

class Problem
{
    public static void Main ()
    {
        int[] x = Enumerable.Range(0, 2).Select(
            z => Console.ReadLine().Split().Sum(y => int.Parse(y))
            ).ToArray();

        if (x[0] == x[1])
            Console.WriteLine("Tie");
        else
            Console.WriteLine(x[1] > x[0] ? "Emma" : "Gunnar");
    }
}
