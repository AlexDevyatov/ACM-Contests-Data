//Solution by lukasP (Lukáš Poláček)
//Use explicit formula for Catalan numbers
using System;
using System.Linq;
using System.Numerics;

class Catalan
{
    public static void Main()
    {
        BigInteger res = Enumerable.Range(2, int.Parse(Console.ReadLine()))
            .Aggregate(BigInteger.One, (x, y) => x * (4 * y - 2) / (y + 1));

        Console.WriteLine(res);
    }
}
