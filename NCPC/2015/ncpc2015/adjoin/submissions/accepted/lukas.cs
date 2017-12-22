//Solution by lukasP (Lukáš Poláček)
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

class Problem
{
    static int f(int x) { return (x + 1) / 2; }

    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);
        int[] y = reader.ReadLine().Split().Select(int.Parse).ToArray();
        int n = y[0], m = y[1];

        var g = Enumerable.Range(0, n).Select(x => new List<int> ()).ToList();
        List<int> cnt = Enumerable.Repeat(0, n).ToList();
        foreach (int i in Enumerable.Range(0, m))
        {
            y = reader.ReadLine().Split().Select(int.Parse).ToArray();
            int a = y[0], b = y[1];
            g[a].Add(b);
            g[b].Add(a);
            cnt[a]++;
            cnt[b]++;
        }

        List<int> dist = Enumerable.Repeat(0, n).ToList();
        for (Queue<int> q = new Queue<int> (Enumerable.Range(0, n).Where(x => cnt[x] == 1));
             q.Count > 0; q.Dequeue())
        {
            int u = q.Peek();
            foreach (int v in g[u].Where(x => --cnt[x] == 1))
            {
                q.Enqueue(v);
                dist[v] = dist[u] + 1;
            }
        }

        List<int> type = Enumerable.Repeat(-1, n).ToList();
        foreach (int i in Enumerable.Range(0, n))
        {
            if (g[i].All(x => dist[x] <= dist[i]))
            {
                type[i] = Convert.ToInt32(g[i].Any(x => dist[x] == dist[i]));
                if (type[i] > 0 && !g[i].Any(x => dist[x] == dist[i] && x < i))
                    type[i] = -1;
            }
        }

        List<int> components = Enumerable.Range(0, n).Where(x => type[x] >= 0)
            .Select(x => dist[x] * 2 + type[x])
            .OrderBy(x => -x)
            .ToList();

        int res = components[0];
        if (components.Count > 1)
            res = Math.Max(res, 1 + f(components[0]) + f(components[1]));
        if (components.Count > 2)
            res = Math.Max(res, 2 + f(components[1]) + f(components[2]));

        Console.WriteLine(res);
    }
}
