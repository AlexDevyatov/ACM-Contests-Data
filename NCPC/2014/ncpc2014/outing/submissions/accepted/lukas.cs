//Solution by lukasP (Lukáš Poláček)
//Use union find to check the components and then run knapsack
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

class Problem
{
    class UnionFind {
        List<int> e;

        public UnionFind(int n)
        {
            e = Enumerable.Repeat(-1, n).ToList();
        }

        public void Join(int a, int b)
        {
            a = Find(a); b = Find(b);
            if (a == b) return;
            if (e[a] > e[b])
            {
                int tmp = a;
                a = b;
                b = tmp;
            }
            e[a] += e[b];
            e[b] = a;
        }

        public int Find(int x)
        {
            if (e[x] < 0) return x;
            return e[x] = Find(e[x]);
        }

        public int Size(int x)
        {
            return -e[Find(x)];
        }
    }

    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);

        int[] aa = reader.ReadLine().Split().Select(y => int.Parse(y)).ToArray();
        int n = aa[0], k = aa[1];

        int[] g = reader.ReadLine().Split().Select(y => int.Parse(y) - 1).ToArray();
        int[] cnt = Enumerable.Repeat(0, n).ToArray();
        foreach (int x in g)
            cnt[x]++;

        UnionFind uf = new UnionFind(n);
        foreach (int i in Enumerable.Range(0, n))
            uf.Join(i, g[i]);

        var q = new Queue<int> (Enumerable.Range(0, n).Where(x => cnt[x] == 0));
        while (q.Count > 0)
        {
            int u = q.Dequeue();
            if (--cnt[g[u]] == 0)
                q.Enqueue(g[u]);
        }

        UnionFind uf2 = new UnionFind(n);
        foreach (int i in Enumerable.Range(0, n).Where(x => cnt[x] == 1))
            uf2.Join(i, g[i]);

        var components = Enumerable.Range(0, n).GroupBy(x => uf.Find(x));
        List<bool> poss = Enumerable.Repeat(false, k + 1).ToList();
        poss[0] = true;
        foreach (var comp in components)
        {
            int down = uf2.Size(comp.First(x => cnt[x] == 1));
            int up = comp.Count();

            for (int j = k - down; j >= 0; j--) if (poss[j])
                for (int i = down; i <= up && i + j <= k; i++)
                    poss[j + i] = true;
        }

        Console.WriteLine(Enumerable.Range(0, k + 1).Last(x => poss[x]));
    }
}
