
//Solution by lukasP (Lukáš Poláček)
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

class Problem
{
    class WorkPair
    {
        public int first, second;
        public int total;
    }

    static bool Enough(int i, int j, int[] cap)
    {
        if (i != j) return cap[i] >= 1 && cap[j] >= 1;
        return cap[i] >= 2;
    }

    static bool FillKayaks(int speed, IEnumerable<WorkPair> candidates, int[] m, int[] c)
    {
        int done = 0;
        foreach (var cand in candidates)
        {
            int x = cand.first, y = cand.second;
            while (Enough(x, y, m) && c[done] * cand.total >= speed)
            {
                done++;
                m[x]--;
                m[y]--;
                if (done == c.Count()) return true;
            }
        }
        return false;
    }

    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);
        int[] n = reader.ReadLine().Split().Select(int.Parse).ToArray();
        int[] s = reader.ReadLine().Split().Select(int.Parse).ToArray();

        var candidates =
            from i in Enumerable.Range(0, 3)
            from j in Enumerable.Range(0, 3)
            orderby s[i] + s[j]
            select new WorkPair{first = i, second = j, total = s[i] + s[j]};

        int[] c = reader.ReadLine().Split().Select(int.Parse).OrderBy(x => -x).ToArray();

        int low = 0, high = c[0] * s[2] * 2 + 1;
        while (low + 1 < high)
        {
            int speed = (low + high) / 2;
            int[] m = new int[3];
            Array.Copy(n, m, 3);

            if (FillKayaks(speed, candidates, m, c)) low = speed;
            else high = speed;
        }

        Console.WriteLine(low);
    }
}
