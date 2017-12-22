// Solution by lukasP (Lukáš Poláček)
// Monte Carlo
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

        Random rnd = new Random();
        double win = 0, tie = 0;
        int iterations = 1000000;
        // Monte Carlo wants to distinguish two random variables, one with expected value 1/2 and
        // another with 1/2 + 1/300. Doing 1 million iterations makes the error probability less
        // than 1% according to Chernoff bound.

        List<List<int>> x = Enumerable.Range(0, 2).Select(
                z => reader.ReadLine().Split().Select(y => int.Parse(y)).ToList()
                ).ToList();
        foreach (int q in Enumerable.Range(0, iterations))
        {
            int[] cur = {0, 0};
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 4; j += 2)
                    cur[i] += rnd.Next(x[i][j], x[i][j + 1] + 1);
            }
            if (cur[0] < cur[1])
                win += 1;
            else if (cur[0] == cur[1])
                tie += 1;
        }

        win /= iterations;
        tie /= iterations;
        double sum = win * 2 + tie;
        if (Math.Abs(sum - 1) < 1.0 / 300)
            Console.WriteLine("Tie");
        else
            Console.WriteLine((sum > 1) ? "Emma" : "Gunnar");
    }
}
