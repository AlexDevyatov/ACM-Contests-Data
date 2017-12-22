//Solution by lukasP (Lukáš Poláček)
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

class Problem
{
    class Node {
        public int s { get; set; }
        public int e { get; set; } // start and end of the interval
        public int Max { get; set; }
        public int Add { get; set; }
        public int GetRangeMax() { return Max + Add; }
        public Node(int s, int e)
        {
            this.s = s;
            this.e = e;
            Max = 0;
            Add = 0;
        }
    };

    struct Tree {
        int n;
        List<Node> s;
        public Tree(int _n) {
            n = 1; while (n < _n) n *= 2;
            int fn = n;
            s = Enumerable.Range(0, 2 * n).Select(x => new Node(x - fn, x - fn + 1)).ToList();
            foreach (int i in Enumerable.Range(1, n - 1).Reverse())
                s[i] = new Node(s[2 * i].s, s[2 * i + 1].e);
        }

        public int Query(int a, int b) { return que(1, a, b); }
        public void Update(int a, int b) { upd(1, a, b); }

        int que(int pos, int a, int b) {
            if (a >= b) return 0;
            if (a == s[pos].s && b == s[pos].e) return s[pos].GetRangeMax();
            int m = (s[pos].s + s[pos].e) / 2;
            return Math.Max(que(2 * pos, a, Math.Min(b, m)),
                            que(2 * pos + 1, Math.Max(a, m), b))
                   + s[pos].Add;
        }

        void upd(int pos, int a, int b) {
            if (a >= b) return;
            Node cur = s[pos];
            if (a == cur.s && b == cur.e)
            {
                cur.Add++;
                return;
            }
            int m = (cur.s + cur.e) / 2;
            upd(2 * pos, a, Math.Min(b, m));
            upd(2 * pos + 1, Math.Max(a, m), b);
            cur.Max = Math.Max(s[2 * pos].GetRangeMax(), s[2 * pos + 1].GetRangeMax());
        }
    };

    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);
        int[] a = reader.ReadLine().Split().Select(int.Parse).ToArray();
        int n = a[0], k = a[1];

        var events = new List<Tuple<int, int>> ();
        var points = new SortedSet<int> ();
        foreach (int i in Enumerable.Range(0, n))
        {
            int[] y = reader.ReadLine().Split().Select(int.Parse).ToArray();
            events.Add(Tuple.Create(y[0], y[1]));
            points.Add(y[0]);
            points.Add(y[1]);
        }

        var ord = new Dictionary<int, int> ();
        int u = 0;
        foreach (int x in points)
            ord[x] = u++;

        int res = 0;
        Tree t = new Tree(points.Count);
        foreach (var r in events.OrderBy(x => x.Item2))
        {
            int x = ord[r.Item1], y = ord[r.Item2];
            int q = t.Query(x, y);
            if (q < k)
            {
                t.Update(x, y);
                res++;
            }
        }
        Console.WriteLine(res);
    }
}
