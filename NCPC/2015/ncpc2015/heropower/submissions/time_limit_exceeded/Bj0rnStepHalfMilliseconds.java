import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.OutputStream;

public class Bj0rnStepHalfMilliseconds {
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

        int bonusFromPhrase(int phrase)
        {
            int bonus = fromPhraseBonus[phrase];
            if (bonus != -1)
                return bonus;
            else
            {
                int doubleSP = 0;
                int noteAt = phrases[phrase].start;
                int noteAfter = noteAt;
                int activePhrase = phrase;
                int phraseAfter = activePhrase + 1;

                // Slow loop - step half a millisecond at a time.
                for (int doublePosition = notes[phrases[phrase].start] * 2; doublePosition <= notes[notes.length-1] * 2;
                     doublePosition++,
                         doubleSP += activePhrase < phrases.length && doublePosition > notes[phrases[activePhrase].start] * 2 && doublePosition <= notes[phrases[activePhrase].end] * 2 ? 1 : 0,
                         activePhrase += activePhrase < phrases.length && doublePosition == notes[phrases[activePhrase].end] * 2 ? 1 : 0)
                {
                    if (doublePosition > notes[noteAt] * 2)
                        noteAt++;
                    if (noteAfter < notes.length && doublePosition + doubleSP > notes[noteAfter] * 2)
                        noteAfter++;
                    if (phraseAfter < phrases.length && doublePosition + doubleSP > notes[phrases[phraseAfter].start] * 2)
                        phraseAfter++;
                    int bonusOnActivation = noteAfter - noteAt + bonusFromPhrase(phraseAfter);
                    bonus = bonusOnActivation > bonus ? bonusOnActivation : bonus;
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
