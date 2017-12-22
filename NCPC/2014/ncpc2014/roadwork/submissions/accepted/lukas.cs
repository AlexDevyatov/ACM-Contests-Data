//Solution by lukasP (Lukáš Poláček)
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

class Problem
{
    static void imprMin(ref int a, int b)
    {
        a = Math.Min(a, b);
    }

    static void imprMax(ref int a, int b)
    {
        a = Math.Max(a, b);
    }

    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);

        int[] xx = reader.ReadLine().Split().Select(z => int.Parse(z)).ToArray();
        int n = xx[1], t = xx[0];

        List<Tuple<int, int>>[] q = Enumerable.Range(0, 2)
            .Select(z => new List<Tuple<int, int>> ()).ToArray();
        foreach (int i in Enumerable.Range(0, n))
        {
            string[] ss = reader.ReadLine().Split();
            int a = int.Parse(ss[1]);
            int r = int.Parse(ss[2]);

            q[Convert.ToInt32(ss[0] == "W")].Add(Tuple.Create(a, r));
        }

        q = q.OrderBy(z => z.Count).ToArray();
        int[,,,] time = new int[2, q[0].Count + 1, n + 1, 2];
        time[0, 0, 0, 0] = time[0, 0, 0, 1] = -3;
        for (int proc = 0; proc < n; proc++)
        {
            int nproc = (proc + 1) % 2;
            for (int east = 0; east <= q[0].Count && east <= proc + 1; east++)
                for (int irr = 0; irr <= proc; irr++)
                    for (int side = 0; side < 2; side++)
                        time[nproc, east, irr, side] = 1234567890;

            for (int east = Math.Max(0, proc - q[1].Count);
                    east <= q[0].Count && east <= proc; east++)
                for (int irr = 0; irr <= proc; irr++)
                    for (int side = 0; side < 2; side++)
            {
                int[] c = {east, proc - east};
                foreach (int nside in Enumerable.Range(0, 2).Where(z => c[z] < q[z].Count))
                {
                    Tuple<int, int> w = q[nside][c[nside]];

                    int nirr = irr, ntime = w.Item1 + t;
                    if (nside == side)
                        imprMax(ref ntime, time[proc % 2, east, irr, side] + 3);
                    else
                        imprMax(ref ntime, time[proc % 2, east, irr, side] + t);

                    if (ntime > w.Item2 + w.Item1 + t) nirr++;
                    int neast = east + 1 - nside;
                    imprMin(ref time[nproc, neast, nirr, nside], ntime);
                }
            }
        }


        for (int irr = 0; irr <= n; irr++)
            for (int side = 0; side < 2; side++)
                if (time[n % 2, q[0].Count, irr, side] < 1234567890)
                {
                    Console.WriteLine(irr);
                    return;
                }
    }
}
