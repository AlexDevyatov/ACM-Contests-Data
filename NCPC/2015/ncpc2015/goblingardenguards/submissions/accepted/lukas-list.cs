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

        List<List<int>> columns = Enumerable.Range(0, 10001).Select(x => new List<int> ()).ToList();
        foreach (int i in Enumerable.Range(0, n))
        {
            int[] y = reader.ReadLine().Split().Select(int.Parse).ToArray();
            columns[y[0]].Add(y[1]);
        }
        foreach (var x in columns)
            x.Sort();

        int q = int.Parse(reader.ReadLine());
        foreach (int i in Enumerable.Range(0, q))
        {
            int[] z = reader.ReadLine().Split().Select(int.Parse).ToArray();
            int x = z[0], y = z[1], r = z[2];
            for (int j = Math.Max(0, x - r); j <= x + r; j++)
                if (j < columns.Count && columns[j].Count > 0)
                {
                    int d = Math.Abs(x - j);
                    int down = (int)Math.Ceiling(y - pytag(r, d));
                    int index = columns[j].BinarySearch(down);
                    if (index < 0) index = ~index;
                    else
                    {
                        while (index >= 0 && columns[j][index] == down)
                            index--;
                        index++;
                    }

                    int up = 2 * y - down;
                    int index2 = columns[j].BinarySearch(up);
                    if (index2 < 0) index2 = ~index2;
                    else while (index2 < columns[j].Count && columns[j][index2] == up)
                        index2++;

                    if (index2 > index)
                        columns[j].RemoveRange(index, index2 - index);
                }
        }

        Console.WriteLine(columns.Sum(x => x.Count));
    }
}
