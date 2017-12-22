//Solution by lukasP (Lukáš Poláček)
using System;
using System.Linq;

class Problem
{
    public static void Main ()
    {
        string s = Console.ReadLine();
        Console.WriteLine(Enumerable.Range(0, s.Length).Count(i => "PER"[i % 3] != s[i]));
    }
}
