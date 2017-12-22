import java.util.*;
import java.util.stream.*;

public class Lukas
{
    public static void main(String[] args)
    {
        final String s = (new Scanner(System.in)).next();
        long res = IntStream.range(0, s.length())
            .filter(i -> "PER".charAt(i % 3) != s.charAt(i)).count();
        System.out.println(res);
    }
}
