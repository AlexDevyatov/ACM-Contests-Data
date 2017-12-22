//Solution by lukasP (Lukáš Poláček)
//Sort of like a Kruskal algorithm for minimum spanning tree
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Globalization;
using System.Threading;
using System.Diagnostics;

class Problem
{
    struct Event
    {
        public int x, y;
        public double dist;
    }

    public static int Main ()
    {
        Scanner sc = new Scanner();
        int n = sc.NextInt();
        List<Complex> pos = new List<Complex> ();
        foreach (int i in Enumerable.Range(0, n))
        {
            int x = sc.NextInt(), y = sc.NextInt();
            pos.Add(new Complex(x, y));
        }

        var g = Enumerable.Range(0, n).Select(x => new List<int> ()).ToList();
        foreach (int i in Enumerable.Range(0, sc.NextInt()))
        {
            int a = sc.NextInt(), b = sc.NextInt();
            a--; b--;
            g[a].Add(b);
            g[b].Add(a);
        }

        List<Event> events = (
            from a in Enumerable.Range(0, n)
            from b in Enumerable.Range(0, n)
            select new Event{x = a, y = b, dist = (pos[b] - pos[a]).Magnitude}
        ).ToList();

        List<int> comp = Enumerable.Range(0, n * n).ToList();
        List<double> dist = Enumerable.Repeat(-1.0, n * n).ToList();
        List<List<int>> members = Enumerable.Range(0, n * n)
            .Select(y => new List<int> {y}).ToList();
        List<bool> seen = Enumerable.Repeat(false, n * n).ToList();

        foreach (Event eve in events.OrderBy(x => -x.dist))
        {
            seen[eve.x * n + eve.y] = true;

            var candidates = g[eve.x].Select(z => z * n + eve.y)
                .Concat(g[eve.y].Select(z => eve.x * n + z))
                .Where(c => seen[c]);
            foreach (int q in candidates)
            {
                int i1 = comp[eve.x * n + eve.y], i2 = comp[q];
                if (i1 == i2) continue;

                if (members[i1].Count > members[i2].Count)
                {
                    int tmp = i2; i2 = i1; i1 = tmp;
                }

                foreach (int u in members[i1])
                {
                    int rid = (u % n) * n + u / n;
                    if (comp[rid] == i2)
                        dist[u] = dist[rid] = eve.dist;
                }
                foreach (int u in members[i1])
                    comp[u] = i2;

                members[i2].AddRange(members[i1]);
                members[i1].Clear();
            }
        }

        Thread.CurrentThread.CurrentCulture = System.Globalization.CultureInfo.InvariantCulture;
        foreach (int x in Enumerable.Range(0, sc.NextInt()))
        {
            int a = sc.NextInt() - 1;
            int b = sc.NextInt() - 1;
            Debug.Assert(dist[a * n + b] > 0.1);
        }

        return 42;
    }
}

public class NoMoreTokensException : Exception
{
}

public class Tokenizer
{
    string[] tokens = new string[0];
    private int pos;
    StreamReader reader;

    public Tokenizer(Stream inStream)
    {
        var bs = new BufferedStream(inStream);
        reader = new StreamReader(bs);
    }

    public Tokenizer() : this(Console.OpenStandardInput())
    {
        // Nothing more to do
    }

    private string PeekNext()
    {
        if (pos < 0)
            // pos < 0 indicates that there are no more tokens
            return null;
        if (pos < tokens.Length)
        {
            if (tokens[pos].Length == 0)
            {
                ++pos;
                return PeekNext();
            }
            return tokens[pos];
        }
        string line = reader.ReadLine();
        if (line == null)
        {
            // There is no more data to read
            pos = -1;
            return null;
        }
        // Split the line that was read on white space characters
        tokens = line.Split(null);
        pos = 0;
        return PeekNext();
    }

    public bool HasNext()
    {
        return (PeekNext() != null);
    }

    public string Next()
    {
        string next = PeekNext();
        if (next == null)
            throw new NoMoreTokensException();
        ++pos;
        return next;
    }
}


public class Scanner : Tokenizer
{

    public int NextInt()
    {
        return int.Parse(Next());
    }

    public long NextLong()
    {
        return long.Parse(Next());
    }

    public float NextFloat()
    {
        return float.Parse(Next());
    }

    public double NextDouble()
    {
        return double.Parse(Next());
    }
}


public class BufferedStdoutWriter : StreamWriter
{
    public BufferedStdoutWriter() : base(new BufferedStream(Console.OpenStandardOutput()))
    {
    }
}
