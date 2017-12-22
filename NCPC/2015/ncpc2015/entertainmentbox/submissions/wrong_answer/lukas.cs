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
        int[] a = reader.ReadLine().Split().Select(int.Parse).ToArray();
        int n = a[0], k = a[1];

        var events = new List<Tuple<int, int>> ();
        foreach (int i in Enumerable.Range(0, n))
        {
            int[] y = reader.ReadLine().Split().Select(int.Parse).ToArray();
            events.Add(Tuple.Create(y[0], y[1]));
        }

        var q = new Queue<int> ();
        int res = 0;
        foreach (var r in events.OrderBy(x => x.Item2))
        {
            if (q.Count < k || (q.Count == k && q.Peek() <= r.Item1))
            {
                if (q.Count > 0 && q.Peek() <= r.Item1)
                    q.Dequeue();
                q.Enqueue(r.Item2);
                res++;
            }
        }
        Console.WriteLine(res);
    }
}
