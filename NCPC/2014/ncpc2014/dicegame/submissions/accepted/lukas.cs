//Solution by lukasP (Lukáš Poláček)
//Construct the whole probability distributions
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

        List<double> pr = Enumerable.Repeat(0.0, 210).ToList();
        double win = 0, tie = 0;
        for (int i = 0; i < 2; i++)
        {
            int[] x = reader.ReadLine().Split().Select(y => int.Parse(y)).ToArray();

            double sz = (x[1] - x[0] + 1) * (x[3] - x[2] + 1);
            for (int j = x[0]; j <= x[1]; j++)
                for (int l = x[2]; l <= x[3]; l++)
                {
                    if (i == 1)
                    {
                        win += pr[j + l - 1] / sz;
                        tie += (pr[j + l] - pr[j + l - 1]) / sz;
                    }
                    else
                        pr[j + l] += 1 / sz;
                }

            if (i == 0) for (int j = 1; j < pr.Count; j++)
                pr[j] += pr[j - 1];
        }

        double sum = win * 2 + tie;
        if (Math.Abs(sum - 1) < 1e-9)
            Console.WriteLine("Tie");
        else
           Console.WriteLine(sum > 1 ? "Emma" : "Gunnar");
    }
}
