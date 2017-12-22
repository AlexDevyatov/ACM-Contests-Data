import java.util.*;

public class pehrs{
    public static void main(String[] args){
        Scanner io = new Scanner(System.in);
        int l = io.nextInt();
        int r = io.nextInt();
        if (l == 0 && r == 0) {
            System.out.println("Not a moose");

        } else {
            if (l == r ) {
                System.out.println("Even "+(l+r));
            } else {
                System.out.println("Odd "+Math.max(l, r)*2);
            }
        }
    }
}
