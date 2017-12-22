//Solution by lukasP (Lukáš Poláček)
//2.31^k solution, coming from the recurrence T(k) = T(k-1) + 3T(k-2)
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

class Problem
{
    static List<int> deg, comp;
    static List<List<int>> h;

    static void take(int i)
    {
        deg[i] = -1;
        foreach (int j in h[i])
            if (deg[j] >= 0)
        {
            deg[j] = -1;
            foreach (int w in h[j])
                deg[w]--;
        }
    }

    static bool go(int rem)
    {
        if (rem == 0) return true;
        if (comp.All(z => deg[z] < 0)) return false;

        int pos = comp.Where(z => deg[z] >= 0).OrderBy(z => deg[z]).First();
        var ndeg = deg.ToList();

        take(pos);
        if (go(rem - 1))
            return true;
        deg = ndeg.ToList();

        if (deg[pos] >= 2)
        {
            List<int> nei = h[pos].Where(x => deg[x] >= 0).ToList();
            int ss = 1 << nei.Count;
            for (int k = 3; k < ss; k++)
            {
                int can = 0;
                for (int l = 0; l < nei.Count; l++)
                    if ((k & (1 << l)) > 0)
                        can++;
                if (can != 2) continue;

                bool succ = true;
                for (int l = 0; l < nei.Count && succ; l++)
                    if ((k & (1 << l)) > 0)
                {
                    if (deg[nei[l]] <= 0) succ = false;
                    else take(nei[l]);
                }

                if (succ && go(rem - can)) return true;
                deg = ndeg.ToList();
            }
        }

        return false;
    }

    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);
        int d = int.Parse(reader.ReadLine());
        int n = int.Parse(reader.ReadLine());
        if (d * 5 - 4 <= n)
        {
            Console.WriteLine("possible");
            return;
        }

        deg = Enumerable.Repeat(0, n).ToList();
        h = Enumerable.Range(0, n)
            .Select(z => reader.ReadLine().Split().Select(x => int.Parse(x) - 1).Skip(1).ToList())
            .ToList();

        List<bool> def = Enumerable.Repeat(false, n).ToList();
        int total = 0;
        for (int i = 0; i < n && total < d; i++)
            if (!def[i])
            {
                Queue<int> q = new Queue<int> ();
                q.Enqueue(i);
                def[i] = true;
                comp = new List<int> ();
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
                    foreach (int j in comp)
                        deg[j] = h[j].Count;

                    if (go(rem)) best = rem;
                    else break;
                }

                total += best;
            }

        Console.WriteLine(total >= d ? "possible" : "impossible");
    }
}
