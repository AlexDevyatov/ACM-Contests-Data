import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class Bj0rn {
    static class Phrase
    {
        int start, end;
        Phrase(int start, int end) { this.start = start; this.end = end; }
    }

    public static void main(String[] args) {
        Kattio io = new Kattio(System.in);
        int n = io.getInt(), p = io.getInt();
        int[] notes = new int[n];
        for (int i = 0; i < n; i++)
            notes[i] = io.getInt();

        Phrase[] phrases = new Phrase[p];
        int ni = 0;
        for (int i = 0; i < p; i++)
        {
            int position = io.getInt();
            for (; notes[ni] < position; ni++);
            int start = ni;

            position = io.getInt();
            for (; notes[ni] < position; ni++);
            int end = ni;

            phrases[i] = new Phrase(start, end);
        }

        System.out.println(n + new Optimizer(notes, phrases).bonusFromPhrase(0));
    }

    static class Optimizer
    {
        int[] notes;
        Phrase[] phrases;
        int[] fromPhraseBonus;

        Optimizer(int[] notes, Phrase[] phrases)
        {
            this.notes = notes;
            this.phrases = phrases;
            fromPhraseBonus = new int[phrases.length + 1];
            for (int i = 0; i < phrases.length; i++)
                fromPhraseBonus[i] = -1;
            fromPhraseBonus[phrases.length] = 0;
        }

        int bonusFromPhrase(final int phrase)
        {
            int bonus = fromPhraseBonus[phrase];
            if (bonus != -1)
                return bonus;
            else
            {
                int noteAt = phrases[phrase].start;
                int noteAfter = noteAt;
                int activePhrase = phrase;
                int phraseAfter = activePhrase + 1;
                int sp = 0;

                outer:
                while (true)
                {
                    noteAt++;
                    if (activePhrase < phrases.length)
                    {
                        if (noteAt > phrases[activePhrase].start)
                            sp += notes[noteAt] - notes[noteAt - 1];
                        if (noteAt == phrases[activePhrase].end)
                            activePhrase++;
                    }

                    while (notes[noteAfter] < notes[noteAt] + sp)
                    {
                        noteAfter++;
                        if (noteAfter == notes.length)
                        {
                            bonus = Integer.max(bonus, noteAfter - noteAt);
                            break outer;
                        }
                    }

                    while (phraseAfter < phrases.length && noteAfter > phrases[phraseAfter].start)
                    {
                        bonus = Integer.max(bonus, phrases[phraseAfter].start - noteAt + bonusFromPhrase(phraseAfter));
                        phraseAfter++;
                    }
                    bonus = Integer.max(bonus, noteAfter - noteAt + bonusFromPhrase(phraseAfter));
                }
                fromPhraseBonus[phrase] = bonus;
                return bonus;
            }
        }
    }
}

/** Simple yet moderately fast I/O routines.
 *
 * Example usage:
 *
 * Kattio io = new Kattio(System.in, System.out);
 *
 * while (io.hasMoreTokens()) {
 *    int n = io.getInt();
 *    double d = io.getDouble();
 *    double ans = d*n;
 *
 *    io.println("Answer: " + ans);
 * }
 *
 * io.close();
 *
 *
 * Some notes:
 *
 * - When done, you should always do io.close() or io.flush() on the
 *   Kattio-instance, otherwise, you may lose output.
 *
 * - The getInt(), getDouble(), and getLong() methods will throw an
 *   exception if there is no more data in the input, so it is generally
 *   a good idea to use hasMoreTokens() to check for end-of-file.
 *
 * @author: Kattis
 */

class Kattio extends PrintWriter {
    public Kattio(InputStream i) {
        super(new BufferedOutputStream(System.out));
        r = new BufferedReader(new InputStreamReader(i));
    }
    public Kattio(InputStream i, OutputStream o) {
        super(new BufferedOutputStream(o));
        r = new BufferedReader(new InputStreamReader(i));
    }

    public boolean hasMoreTokens() {
        return peekToken() != null;
    }

    public int getInt() {
        return Integer.parseInt(nextToken());
    }

    public double getDouble() {
        return Double.parseDouble(nextToken());
    }

    public long getLong() {
        return Long.parseLong(nextToken());
    }

    public String getWord() {
        return nextToken();
    }



    private BufferedReader r;
    private String line;
    private StringTokenizer st;
    private String token;

    private String peekToken() {
        if (token == null)
            try {
                while (st == null || !st.hasMoreTokens()) {
                    line = r.readLine();
                    if (line == null) return null;
                    st = new StringTokenizer(line);
                }
                token = st.nextToken();
            } catch (IOException e) { }
        return token;
    }

    private String nextToken() {
        String ans = peekToken();
        token = null;
        return ans;
    }
}
