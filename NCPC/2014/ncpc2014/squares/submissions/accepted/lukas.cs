//Solution by lukasP (Lukáš Poláček)
//Sorting lines by directions and then doing magic with hash tables
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;

class Problem
{
    static int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }

    static Complex normalize(Complex a)
    {
        if (a.Imaginary < 0 || (a.Imaginary == 0 && a.Real < 0))
            a *= -1;
        int x = (int)a.Real, y = (int)a.Imaginary;
        int d = gcd(Math.Abs(x), y);
        return new Complex(x / d, y / d);
    }

    static Complex normalize2(Complex a)
    {
        return a.Real > 0 ? a : a * (new Complex(0, -1));
    }

    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);

        int n = int.Parse(reader.ReadLine());
        var lines = Enumerable.Range(0, 2)
            .Select(x => new Dictionary<Complex, List<int>> ()).ToArray();
        for (int i = 0; i < n; i++)
        {
            int[] z = reader.ReadLine().Split().Select(x => int.Parse(x)).ToArray();
            Complex A = new Complex(z[0], z[1]);
            Complex dir = normalize((new Complex(z[2], z[3])) - A);

            int w = Convert.ToInt32(dir.Real > 0);
            if (!lines[w].ContainsKey(normalize2(dir)))
                lines[w][normalize2(dir)] = new List<int> ();

            lines[w][normalize2(dir)].Add((int)(dir.Imaginary * A.Real - dir.Real * A.Imaginary));
        }

        long res = 0;
        foreach (var dir in lines[0].Keys)
            if (lines[1].ContainsKey(dir))
        {
            List<int>[] b = new List<int>[] {lines[0][dir], lines[1][dir]};
            var diff = new Dictionary<int, int> ();
            for (int k = 0; k < 2; k++)
                for (int i = 0; i < b[k].Count; i++)
                    for (int j = 0; j < i; j++)
                    {
                        int dif = Math.Abs(b[k][i] - b[k][j]);
                        if (k == 0)
                        {
                            if (!diff.ContainsKey(dif))
                                diff[dif] = 1;
                            else
                                diff[dif]++;
                        }
                        else if (diff.ContainsKey(dif))
                            res += diff[dif];
                    }
        }

        Console.WriteLine(res);
    }
}
