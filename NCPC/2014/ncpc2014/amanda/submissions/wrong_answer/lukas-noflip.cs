//Solution by lukasP (Lukáš Poláček)
//Doesn't flip the colors if if it would lead to smaller number of built lounges
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

        int[] xx = reader.ReadLine().Split().Select(z => int.Parse(z)).ToArray();
        int n = xx[0], m = xx[1];

        List<bool> def = Enumerable.Repeat(false, n).ToList();
        List<bool> col = Enumerable.Repeat(false, n).ToList();
        List<List<int>> g = Enumerable.Range(0, n).Select(z => new List<int> ()).ToList();
        bool ok = true;
        foreach (int i in Enumerable.Range(0, m))
        {
            xx = reader.ReadLine().Split().Select(z => int.Parse(z)).ToArray();
            int a = xx[0], b = xx[1], c = xx[2];
            a--; b--;

            if (c != 1)
            {
                bool color = c == 2;
                if ((def[a] && color ^ col[a]) || (def[b] && color ^ col[b]))
                    ok = false;
                col[a] = col[b] = color;
                def[a] = def[b] = true;
            }
            else
            {
                g[a].Add(b);
                g[b].Add(a);
            }
        }

        Queue<int> q = new Queue<int>(Enumerable.Range(0, n).Where(z => def[z]));
        while (q.Count > 0)
        {
            int u = q.Dequeue();
            if (g[u].Any(z => def[z] && col[z] == col[u]))
                ok = false;

            foreach (int w in g[u])
                if (!def[w])
            {
                def[w] = true;
                col[w] = !col[u];
                q.Enqueue(w);
            }
        }

        foreach (int i in Enumerable.Range(0, n))
            if (!def[i])
            {
                var comp = new List<int> ();
                q = new Queue<int> ();
                q.Enqueue(i);
                col[i] = true;
                def[i] = true;

                int[] sz = {0, 0};
                while (q.Count > 0)
                {
                    int u = q.Dequeue();
                    if (g[u].Any(z => def[z] && col[z] == col[u]))
                        ok = false;

                    sz[Convert.ToInt32(col[u])]++;
                    comp.Add(u);
                    foreach (int w in g[u]) if (!def[w])
                    {
                        def[w] = true;
                        col[w] = !col[u];
                        q.Enqueue(w);
                    }
                }
            }

        if (!ok)
            Console.WriteLine("impossible");
        else
            Console.WriteLine(col.Count(z => z));
    }
}
