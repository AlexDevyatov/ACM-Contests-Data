//Solution by lukasP (Lukáš Poláček)
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

class Problem
{
    static List<int> deg;
    static List<List<int>> h;
    static int n;
    static SortedSet<Tuple<int, int>> pq;

    static void take(int i)
    {
        pq.Remove(Tuple.Create(deg[i], i));
        foreach (int j in h[i])
        {
            pq.Remove(Tuple.Create(deg[j], j));
            deg[j] = -1;
            foreach (int w in h[j])
                if (pq.Contains(Tuple.Create(deg[w], w)))
            {
                pq.Remove(Tuple.Create(deg[w], w));
                deg[w]--;
                pq.Add(Tuple.Create(deg[w], w));
            }
        }
    }

    static bool go(int rem)
    {
        if (rem == 0)
            return true;
        if (pq.Count == 0)
            return false;

        var bpq = pq;
        var ndeg = deg;

        int pos = pq.Min.Item2;
        take(pos);
        if (go(rem - 1)) return true;
        if (deg[pos] == 1) return false;

        if (deg[pos] == 2)
        {
            pq = bpq;
            deg = ndeg;
            int can = 0;
            foreach (int j in h[pos])
                if (deg[j] >= 1)
                {
                    take(j);
                    can++;
                }
            return can == 2 && go(rem - 2);
        }

        List<int> nei = h[pos].Where(z => deg[z] >= 0).ToList();
        int ss = 1 << nei.Count;

        for (int k = 3; k < ss; k++)
        {
            pq = bpq;
            deg = ndeg;

            bool unsucc = false;
            int can = 0;
            for (int l = 0; l < nei.Count; l++)
                if ((k & (1 << l)) > 0)
            {
                if (deg[l] <= 0) unsucc = true;
                else take(l);
                can++;
            }

            if (!unsucc && go(rem - can))
                return true;
        }

        return false;
    }

    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);
        int d = int.Parse(reader.ReadLine());
        n = int.Parse(reader.ReadLine());
        if (d * 5 - 4 <= n)
        {
            Console.WriteLine("possible");
            return;
        }

        deg = Enumerable.Repeat(0, n).ToList();
        h = new List<List<int>> ();
        foreach (int i in Enumerable.Range(0, n))
            h.Add(reader.ReadLine().Split().Select(x => int.Parse(x) - 1).Skip(1).ToList());

        List<bool> def = Enumerable.Repeat(false, n).ToList();
        int total = 0;
        for (int i = 0; i < n && total < d; i++)
            if (!def[i])
            {
                Queue<int> q = new Queue<int> ();
                q.Enqueue(i);
                def[i] = true;
                List<int> comp = new List<int> ();
                while (q.Count > 0)
                {
                    int u = q.Dequeue();
                    comp.Add(u);
                    foreach (int w in h[u])
                        if (!def[w])
                    {
                        def[w] = true;
                        q.Enqueue(w);
                    }
                }

                int best = 1;
                for (int rem = 2; rem <= d; rem++)
                {
                    pq = new SortedSet<Tuple<int, int>> ();
                    foreach (int j in comp)
                    {
                        deg[j] = h[j].Count;
                        pq.Add(Tuple.Create(deg[j], j));
                    }

                    if (go(rem)) best = rem;
                    else break;
                }

                total += best;
            }

        // Console.WriteLine(total);
        Console.WriteLine(total >= d ? "possible" : "impossible");
    }
}
