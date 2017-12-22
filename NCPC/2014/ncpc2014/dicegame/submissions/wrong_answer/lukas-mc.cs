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
        int iterations = 50000;

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
        if (Math.Abs(sum - 1) < 1.0 / 200)
            Console.WriteLine("Tie");
        else
            Console.WriteLine((sum > 1) ? "Emma" : "Gunnar");
    }
}
