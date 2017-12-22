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
        int[] w = reader.ReadLine().Split().Select(int.Parse).ToArray();
        int n = w[0], p = w[1];
        List<int> t = reader.ReadLine().Split().Select(int.Parse).ToList();
        Dictionary<int, int> ord = Enumerable.Range(0, n).ToDictionary(x => t[x], x => x);

        List<int> next = new List<int> ();
        List<int> starts = Enumerable.Repeat(0, p).ToList();
        List<int> totpow = new List<int> ();
        foreach (int i in Enumerable.Range(0, p))
        {
            w = reader.ReadLine().Split().Select(int.Parse).ToArray();
            int s = w[0], e = w[1];
            starts[i] = ord[s];
            next.AddRange(Enumerable.Repeat(i, starts[i] - next.Count));

            int last = totpow.Count == 0 ? 0 : totpow.Last();
            totpow.AddRange(Enumerable.Repeat(last, starts[i] + 1 - totpow.Count));
            for (int j = ord[s]; j < ord[e]; j++)
                totpow.Add(totpow.Last() + t[j + 1] - t[j]);
        }
        next.AddRange(Enumerable.Repeat(p, n - next.Count));
        totpow.AddRange(Enumerable.Repeat(totpow.Last(), n - totpow.Count));

        List<int> best = Enumerable.Repeat(0, p + 1).ToList();
        foreach (int i in Enumerable.Range(0, p))
        {
            int point = starts[i];
            for (int j = point; j < n; j++)
            {
                while (point + 1 < n && totpow[point + 1] - totpow[starts[i]] <= t[j] - t[point + 1])
                    point++;
                best[next[j]] = Math.Max(best[next[j]], best[i] + (j - point));
            }
        }

        Console.WriteLine(best[p] + n);
    }
}
