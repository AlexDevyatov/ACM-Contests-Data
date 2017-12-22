//Solution by lukasP (Lukáš Poláček)
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Globalization;

class Problem
{
    class Node {
        public Dictionary<string, int> next = new Dictionary<string, int> ();
        public Dictionary<string, int> answers = new Dictionary<string, int> ();
        public double probability { get; set; }  // probability of being right if picking the most common answer in the subtree
        public int total_answers { get; set; }
    }

    static List<Node> nodes = Enumerable.Repeat(new Node(), 1).ToList();
    static double Traverse(int j, double[] best, int bpos, int left)
    {
        if (left == 0) return 0;
        double now = nodes[j].probability + best[bpos]; // answer now and move to the next question
        double move = nodes[j].next.Values
            .Sum(x => Traverse(x, best, bpos + 1, left - 1) * nodes[x].total_answers);

        return Math.Max(move / nodes[j].total_answers, now);
    }

    static void AddToNode(string answer, int index)
    {
        if (nodes[index].answers.ContainsKey(answer)) nodes[index].answers[answer]++;
        else nodes[index].answers.Add(answer, 1);
    }

    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);
        int[] y = reader.ReadLine().Split().Select(int.Parse).ToArray();
        int t = y[0], n = y[1];

        foreach (int i in Enumerable.Range(0, n))
        {
            var words = reader.ReadLine().Split();
            string answer = words.Last();

            int index = 0;
            AddToNode(answer, 0);
            foreach (string cur in words.Take(words.Count() - 1))
            {
                if (!nodes[index].next.ContainsKey(cur))
                {
                    nodes[index].next.Add(cur, nodes.Count());
                    nodes.Add(new Node());
                }
                index = nodes[index].next[cur];
                AddToNode(answer, index);
            }
        }

        foreach (Node node in nodes)
        {
            int s = node.answers.Values.Sum();
            node.probability = node.answers.Values.Max() / (double)s;
            node.total_answers = s;
        }

        double[] best = new double[t + 1];
        for (int i = t - 1; i >= 0; i--)
            best[i] = Traverse(0, best, i + 1, t - i);

        Console.WriteLine(best[0].ToString("#.############", CultureInfo.GetCultureInfo("en-GB")));
    }
}
