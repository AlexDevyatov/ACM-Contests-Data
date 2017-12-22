object per {
    def main(args: Array[String]) {
        var line = scala.io.StdIn.readLine()
        val Array(l, r) = line.split(" ").map(_.toLong)
        if (l == 0 && r == 0) {
            Console.out.println("Not a moose");
        } else if (l == r) {
            Console.out.println("Even " + (l+r));
        } else {
            Console.out.println("Odd " + 2*Math.max(l,r));
        }
   }
}
