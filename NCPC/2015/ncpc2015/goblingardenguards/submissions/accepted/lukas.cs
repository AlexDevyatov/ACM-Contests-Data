//Solution by lukasP (Lukáš Poláček)
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

class Problem
{
    static double pytag(double r, double x)
    {
        return Math.Sqrt(r * r - x * x);
    }

    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);
        int n = int.Parse(reader.ReadLine());

        List<SortedSet<int>> columns = Enumerable.Range(0, 10001).Select(x => new SortedSet<int> ())
                                       .ToList();
        List<Dictionary<int, int>> multiple = Enumerable.Range(0, 10001)
                                              .Select(x => new Dictionary<int, int> ()).ToList();
        foreach (int i in Enumerable.Range(0, n))
        {
            int[] y = reader.ReadLine().Split().Select(int.Parse).ToArray();
            columns[y[0]].Add(y[1]);
            if (multiple[y[0]].ContainsKey(y[1]))
                multiple[y[0]][y[1]]++;
            else multiple[y[0]][y[1]] = 1;
        }

        int q = int.Parse(reader.ReadLine());
        foreach (int i in Enumerable.Range(0, q))
        {
            int[] z = reader.ReadLine().Split().Select(int.Parse).ToArray();
            int x = z[0], y = z[1], r = z[2];
            for (int j = Math.Max(0, x - r); j <= x + r; j++)
                if (j < columns.Count && columns[j].Count > 0)
                {
                    int d = Math.Abs(x - j);
                    int up = (int)Math.Floor(y + pytag(r, d));
                    List<int> copy = columns[j].GetViewBetween(2 * y - up, up).Select(b => b).ToList();
                    foreach (int element in copy)
                        columns[j].Remove(element);
                }
        }

        int res = Enumerable.Range(0, 10001).Select(i => columns[i].Sum(e => multiple[i][e])).Sum();
        Console.WriteLine(res);
    }
}
