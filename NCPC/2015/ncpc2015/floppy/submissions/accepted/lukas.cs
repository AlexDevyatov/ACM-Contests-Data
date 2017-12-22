//Solution by lukasP (Lukáš Poláček)
using System;
using System.IO;
using System.Collections;
using System.Linq;

class Problem
{
    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);

        foreach (int cas in Enumerable.Range(0, int.Parse(reader.ReadLine())))
        {
            int[] w = reader.ReadLine().Split().Select(int.Parse).ToArray();
            int t = w[0], n = w[1];
            BitArray can = new BitArray(t + 1, true);

            foreach (int i in Enumerable.Range(0, n))
            {
                w = reader.ReadLine().Split().Select(int.Parse).ToArray();
                int start = w[0], end = w[1];
                int dif = end - start;

                BitArray ncan = new BitArray(t + 1, false);
                for (int j = 0; j < t + 1; j++) if (can[j])
                {
                    if (j >= dif)
                        ncan[j - dif] = true;
                    if (j + dif <= t)
                        ncan[j + dif] = true;
                }
                can = ncan;
            }

            if (!(from bool m in can where m select m).Any())
            {
                Console.WriteLine("impossible");
                return;
            }
        }
        Console.WriteLine("possible");
    }
}
