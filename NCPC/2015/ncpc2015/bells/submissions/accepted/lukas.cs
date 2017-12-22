//Solution by lukasP (Lukáš Poláček)
using System;
using System.Linq;
using System.Collections.Generic;

class Problem
{
    public static IEnumerable<IEnumerable<int>> gen(int n) {
        if (n == 1)
        {
            yield return Enumerable.Repeat(1, 1);
            yield break;
        }

        bool dir = false;
        foreach (IEnumerable<int> enumer in gen(n - 1)) {
            List<int> o = enumer.ToList();
            if (!dir) o.Add(n);
            else o.Insert(0, n);
            yield return o;

            int cur = dir ? 0 : n - 1;
            for (int i = 0; i < n - 1; i++) {
                int pos = cur + (dir ? 1 : -1);
                List<int> newo = new List<int> (o);

                int tmp = newo[cur];
                newo[cur] = newo[pos];
                newo[pos] = tmp;
                yield return newo;

                cur = pos;
                o = newo;
            }
            dir = !dir;
        }
    }

    public static void Main ()
    {
        int n = int.Parse(Console.ReadLine());
        foreach (IEnumerable<int> row in gen(n))
            Console.WriteLine(String.Join(" ", row));
    }
}
