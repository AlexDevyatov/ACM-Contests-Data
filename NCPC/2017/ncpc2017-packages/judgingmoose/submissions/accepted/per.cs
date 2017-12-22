using System;

public class Program {
    public static void Main() {
        string[] split = Console.ReadLine().Split(new char[] { ' ' }, StringSplitOptions.None);
        int l = Int32.Parse(split[0]);
        int r = Int32.Parse(split[1]);
        int val = 2*(l > r ? l : r);
        if (val == 0) { Console.WriteLine("Not a moose"); }
        else if (l == r) { Console.WriteLine("Even " + val); }
        else { Console.WriteLine("Odd " + val); }
    }
}
