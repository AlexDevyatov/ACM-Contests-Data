
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
        int n = a[0], m = a[1];

        int s = 1 << m;
        var distance = Enumerable.Repeat(s, s).ToArray();
        Queue<int> q = new Queue<int> ();
        foreach (int i in Enumerable.Range(0, n))
        {
            int num = Convert.ToInt32(reader.ReadLine(), 2);
            distance[num] = 0;
            q.Enqueue(num);
        }

        int last = 0;
        while (q.Count() > 0)
        {
            int cur = q.Peek();
            last = cur;
            q.Dequeue();
            for (int i = 0; i < m; i++)
            {
                int bit = 1 << i;
                if (distance[cur ^ bit] == s)
                {
                    distance[cur ^ bit] = distance[cur] + 1;
                    q.Enqueue(cur ^ bit);
                }
            }
        }

        Console.WriteLine(Convert.ToString(last, 2).PadLeft(m, '0'));
    }
}
