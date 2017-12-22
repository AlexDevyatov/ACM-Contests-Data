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
        int[] a = reader.ReadLine().Split().Select(int.Parse).ToArray();
        int n = a[0], k = a[1];

        List<int> cnt = Enumerable.Repeat(0, 101001).ToList();
        int res = 0, prefix_sum = 0, last = 0, total = 0;
        foreach (int i in Enumerable.Range(0, n))
        {
            int x = int.Parse(reader.ReadLine()) + 1000;
            cnt[x]++;
            total++;
            for (; last <= x - 1000; last++)
                prefix_sum += cnt[last];
            res = Math.Max(res, (total - prefix_sum + k - 1) / k);
        }
        Console.WriteLine(res);
    }
}
