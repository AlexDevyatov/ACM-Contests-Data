import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.*;

public class AutoCorrectGenerator {

    static int MAX_INPUT_SIZE = 1024*1024 - 30;
    static int MAX_DICT_SIZE = 100000;
    static int MAX_WORD_SIZE = 100000;

    public static class Dictionary {
        public Trie root;
        public List<String> words;
        public List<Trie> wordNodes;
        public int dictSize; // in bytes
        public int noLeafs;
        public int noNodes;
        public int maxWordLength;
        public int maxAutoComplete;
        public int maxBackspace;
        public LetterGenerator generator;

        public String summary() {
            return String.format("noNodes = %d, noWords = %d, maxWordLength = %d, size = %d bytes, noLeafs = %d, maxAutoComplete = %d, maxBackspace = %d",
                    noNodes, words.size(), maxWordLength, dictSize, noLeafs, maxAutoComplete, maxBackspace);
        }

        public void print() {
            for (Trie node : wordNodes) {
                System.out.println(String.format("%s  (%d %d %d)",
                        node.getWord(), node.distance, node.noAutoCompletes, node.noBackspace));
            }
        }
    }

    public static class Trie {
        private Trie[] letter = new Trie[28]; // 26 = autoComplete, 27 = parent
        private int distance = -1; // shortest distance to this node from the root
        private int noAutoCompletes = 0; // min number of auto completes necessary
        private int noBackspace = 0; // min number of backspaces necessary
        private int depth;
        private boolean isLeaf;
        private boolean wordEnd;
        private char c;
        private Trie getParent() { return this.letter[27]; }

        public Trie(Trie parent, char c, int depth) {
            this.letter[27] = parent;
            this.depth = depth;
            this.isLeaf = true;
            this.c = c;
        }

        private void buildWord(StringBuilder sb) {
            if (getParent() != null) {
                getParent().buildWord(sb);
                sb.append(c);
            }
        }

        public String getWord() {
            StringBuilder sb = new StringBuilder(depth + 1);
            buildWord(sb);
            return sb.toString();
        }
    }

    public static void main(String[] args) throws FileNotFoundException {
        int caseNo = 7;

        generateInput(caseNo++, 0, 5000, 0.03, 15, 10000, 3);
//        Seed = 0: noNodes = 2021, noWords = 862, maxWordLength = 15, size = 10000 bytes, noLeafs = 862, maxAutoComplete = 2, maxBackspace = 5
//        Dictionary dict = generateDictionary(0, 5000, 0.03, 15, 10000, 3);

//        Seed = 2: noNodes = 74434, noWords = 36155, maxWordLength = 20, size = 500000 bytes, noLeafs = 36155, maxAutoComplete = 3, maxBackspace = 10
//        Dictionary dict = generateDictionary(2, 200000, 0.1, 20, 500000, 8);
        generateInput(caseNo++, 2, 200000, 0.1, 20, 500000, 8);

//        Seed = 3: noNodes = 164638, noWords = 85851, maxWordLength = 10, size = 800000 bytes, noLeafs = 85851, maxAutoComplete = 2, maxBackspace = 3
//        Dictionary dict = generateDictionary(3, 200000, 0.1, 10, 800000, 7);
        generateInput(caseNo++, 3, 200000, 0.1, 10, 800000, 7);

//        Seed = 2: noNodes = 100000, noWords = 57009, maxWordLength = 8, size = 455697 bytes, noLeafs = 55719, maxAutoComplete = 2, maxBackspace = 2
//        Dictionary dict = generateDictionary(2, 100000, 0.03, 8, 500000, 8);
        generateInput(caseNo++, 2, 100000, 0.03, 8, 500000, 8);
//        Dictionary dict = generateDictionary(11, 200000, 0.03, 15, 800000, 26);
//        Seed = 11: noNodes = 145215, noWords = 74407, maxWordLength = 15, size = 800000 bytes, noLeafs = 74407, maxAutoComplete = 3, maxBackspace = 6
        generateInput(caseNo++, 11, 200000, 0.03, 15, 800000, 26);
//        Dictionary dict = generateDictionary(11, 50000, 0.03, 8, 300000, 5);
//        Seed = 11: noNodes = 50000, noWords = 28654, maxWordLength = 8, size = 243429 bytes, noLeafs = 28005, maxAutoComplete = 2, maxBackspace = 2
        generateInput(caseNo++, 11, 50000, 0.03, 8, 300000, 5);
//        Dictionary dict = generateDictionary(11, 50000, 0.5, 10, 300000, 10);
//        Seed = 11: noNodes = 50000, noWords = 36314, maxWordLength = 10, size = 299999 bytes, noLeafs = 26296, maxAutoComplete = 3, maxBackspace = 3
        generateInput(caseNo++, 11, 50000, 0.5, 10, 300000, 10);
//        Dictionary dict = generateDictionary(21, 10000, 0.01, 1000, 500000, 13);
//        Seed = 21: noNodes = 10000, noWords = 4853, maxWordLength = 158, size = 256247 bytes, noLeafs = 4799, maxAutoComplete = 7, maxBackspace = 32
        generateInput(caseNo++, 21, 10000, 0.01, 1000, 500000, 13);
//        Seed = 20: noNodes = 16061, noWords = 7704, maxWordLength = 190, size = 500000 bytes, noLeafs = 7704, maxAutoComplete = 6, maxBackspace = 62
//        Dictionary dict = generateDictionary(20, 20000, 0.1, 1000, 500000, 26);
        generateInput(caseNo++, 20, 20000, 0.1, 1000, 500000, 26);
//        Seed = 21: noNodes = 10000, noWords = 4577, maxWordLength = 190, size = 298467 bytes, noLeafs = 3953, maxAutoComplete = 6, maxBackspace = 57
//        Dictionary dict = generateDictionary(21, 10000, 0.1, 1000, 500000, 3);
        generateInput(caseNo++, 21, 10000, 0.1, 1000, 500000, 3);
//        Seed = 34: noNodes = 25175, noWords = 12153, maxWordLength = 231, size = 950000 bytes, noLeafs = 12153, maxAutoComplete = 10, maxBackspace = 38
//        Dictionary dict = generateDictionary(34, 50000, 0.1, 1000, 950000, 26);
        generateInput(caseNo++, 34, 50000, 0.1, 1000, 950000, 26);
//        Seed = 34: noNodes = 1000, noWords = 544, maxWordLength = 47, size = 10042 bytes, noLeafs = 486, maxAutoComplete = 4, maxBackspace = 14
        generateInput(caseNo++, 34, 1000, 0.1, 1000, 30000, 26);

//        Seed = 30: noNodes = 1000, noWords = 519, maxWordLength = 46, size = 9922 bytes, noLeafs = 469, maxAutoComplete = 5, maxBackspace = 13
        generateInput(caseNo++, 30, 1000, 0.1, 1000, 10000, 10);


//        for (int seed = 30; seed < 35; seed++) {
//            Dictionary dict = generateDictionary(seed, 1000, 0.1, 1000, 10000, 10);
//            System.out.println("Seed = " + seed + ": " + dict.summary());
//        }

//        generateWordsToType(0, dict, MAX_WORD_SIZE, dict.maxWordLength + 5, MAX_INPUT_SIZE - dict.dictSize, false);
//        System.out.println();
//        System.out.println("WORDS");
//        generateWordsToType(0, dict, 20, 20, 10000, false);
    }

    private static void generateInput(int caseNo,
                                      int seed, // random seed
                                      int noNodes, // generate trie with this many nodes
                                      double wordProb, // probability that an interior node in the trie is a word
                                      int maxWordLength, // maximum length of a word in the dictionary
                                      int maxDictSize, // maximum size (in bytes) of the dictionary, including new line charaters
                                      int noCharacters // size of the alphabet (max 26)
    ) throws FileNotFoundException {
        Dictionary dict = generateDictionary(seed, noNodes, wordProb, maxWordLength, maxDictSize, noCharacters);
        List<String> words = generateWordsToType(0, dict, MAX_WORD_SIZE, dict.maxWordLength + 5, MAX_INPUT_SIZE - dict.dictSize, false);

        if (dict.words.size() > MAX_DICT_SIZE) throw new RuntimeException("Dictionary contains too many words: " + dict.words.size());
        if (words.size() > MAX_WORD_SIZE) throw new RuntimeException("Too many words to type: " + dict.words.size());

        System.out.println("Case #" + caseNo + ": " + dict.summary());

        PrintWriter pw = new PrintWriter(new File(String.format("%02d-generated.in", caseNo)));
        pw.println(dict.wordNodes.size() + " " + words.size());
        for (String word : dict.words) {
            pw.println(word);
        }
        for (String word : words) {
            pw.println(word);
        }
        pw.close();
    }

    private static class NodeGroup {
        private int noAutoCompletes, noBackSpaces;

        public NodeGroup(int noAutoCompletes, int noBackSpaces) {
            this.noAutoCompletes = noAutoCompletes;
            this.noBackSpaces = noBackSpaces;
        }

        @Override
        public boolean equals(Object o) {
            NodeGroup nodeGroup = (NodeGroup) o;
            return noAutoCompletes == nodeGroup.noAutoCompletes && noBackSpaces == nodeGroup.noBackSpaces;
        }

        @Override
        public int hashCode() {
            return 31 * noAutoCompletes + noBackSpaces;
        }
    }

    public static List<String> generateWordsToType(int seed, Dictionary dict, int maxWords, int maxWordLength, int maxWordsSize, boolean includeRoot) {
        int iter = 0, maxIter = maxWords * 10, wordSize = 0;
        ArrayList<String> words = new ArrayList<>();
        // Group nodes into how many autocompletes and backspaces required

        HashMap<NodeGroup, List<Trie>> map = new HashMap<>();
        ArrayList<NodeGroup> groups = new ArrayList<>();

        ArrayList<Trie> tries = new ArrayList<>(dict.wordNodes);
        if (includeRoot) tries.add(dict.root);

        for (Trie node : tries) {
            NodeGroup group = new NodeGroup(node.noAutoCompletes, node.noBackspace);
            if (!map.containsKey(group)) {
                map.put(group, new ArrayList<>());
                groups.add(group);
            }
            map.get(group).add(node);
        }

        Random random = new Random(seed);

        while (words.size() < maxWords && iter++ < maxIter) {
            NodeGroup nodeGroup = groups.get(random.nextInt(groups.size()));
            List<Trie> candidates = map.get(nodeGroup);
            Trie stem = candidates.get(random.nextInt(candidates.size()));
            String word = stem.getWord();

            if (random.nextDouble() < .25 && word.length() > 0) {
                int cut = random.nextInt((1 + word.length()) / 2);
                word = word.substring(0, Math.max(0, word.length() - cut));
            } else {
                int add = random.nextInt(Math.max(3, word.length() / 2));
                StringBuilder sb = new StringBuilder();
                sb.append(word);
                for (int i = 0; i < add && sb.length() < maxWordLength; i++) {
                    sb.append(dict.generator.next());
                }
                word = sb.toString();
            }

            if (word.length() > 0 && word.length() <= maxWordLength && wordSize + word.length() + 1 <= maxWordsSize) {
//                System.out.println(String.format("%s  (%s %d %d %d)", word, stem.getWord(), stem.distance, stem.noAutoCompletes, stem.noBackspace));
                words.add(word);
                wordSize += word.length() + 1;
            }
        }
        return words;
    }

    public static Dictionary generateDictionary(
            int seed, // random seed
            int noNodes, // generate trie with this many nodes
            double wordProb, // probability that an interior node in the trie is a word
            int maxWordLength, // maximum length of a word in the dictionary
            int maxDictSize, // maximum size (in bytes) of the dictionary, including new line charaters
            int noCharacters // size of the alphabet (max 26)
    ) {
        Random random = new Random(seed);
        LetterGenerator generator = new LetterGenerator(random, noCharacters);

        ArrayList<Trie> nodes = new ArrayList<>();
        List<List<Trie>> nodesPerDepth = new ArrayList<>();
        for (int i = 0; i <= maxWordLength; i++) {
            nodesPerDepth.add(new ArrayList<>());
        }

        int iter = 0, noLeafs = 0, dictSize = 0, maxIter = noNodes * 10, maxLength = 0, maxDepth = 0;
        Trie root = new Trie(null, (char) 0, 0);
        root.isLeaf = false;
        nodesPerDepth.get(0).add(root);
        nodes.add(root);

        while (nodes.size() < noNodes && dictSize < maxDictSize && iter++ < maxIter) {

//            Trie node = nodes.get(random.nextInt(nodes.size()));

            int d = random.nextInt(Math.min(maxDepth + 1, maxWordLength));
            Trie node = nodesPerDepth.get(d).get(random.nextInt(nodesPerDepth.get(d).size()));


            if (node.depth >= maxWordLength) continue;

            int let = generator.next() - 'a';
            if (node.letter[let] != null) continue;

            if (node.isLeaf) {
                node.isLeaf = false; // extending existing leaf
                dictSize++;
            } else {
                if (dictSize + node.depth + 2 > maxDictSize) continue;
                noLeafs++; // new branch
                dictSize += (node.depth + 1) + 1; // new word, the +1 is the new line character
            }

            Trie newNode = new Trie(node, (char)('a' + let), node.depth + 1);
            maxLength = Math.max(maxLength, node.depth + 1);
            node.letter[let] = newNode;

//            System.out.println("Creating " + newNode.getWord());
//            System.out.println("noLeafs " + noLeafs);

            maxDepth = Math.max(maxDepth, newNode.depth);
            nodes.add(newNode);
            nodesPerDepth.get(newNode.depth).add(newNode);
        }

        int noWords = 0;
        for (Trie node : nodes) {
            if (node.isLeaf) {
                node.wordEnd = true;
                noWords++;
            }
        }

        ArrayList<Trie> extraWords = new ArrayList<>(nodes);
        randomShuffle(random, extraWords);

        for (Trie node : extraWords) {
            if (node.getParent() == null || node.wordEnd) continue;
            if (random.nextDouble() >= wordProb) continue;
            if (dictSize + node.depth + 1 <= maxDictSize) {
                node.wordEnd = true;
                noWords++;
                dictSize += node.depth + 1;
            } else {
                break;
            }
        }

        ArrayList<Trie> sortedNodes = new ArrayList<>();
        for (Trie node : nodes) {
            if (node.wordEnd) sortedNodes.add(node);
        }
        randomShuffle(random, sortedNodes);

        solve(root, sortedNodes);

        Dictionary dict = new Dictionary();
        dict.root = root;
        dict.dictSize = dictSize;
        dict.maxWordLength = maxLength;
        dict.noLeafs = noLeafs;
        dict.words = new ArrayList<>(sortedNodes.size());
        for (Trie word : sortedNodes) {
            dict.words.add(word.getWord());

            dict.maxAutoComplete = Math.max(dict.maxAutoComplete, word.noAutoCompletes);
            dict.maxBackspace = Math.max(dict.maxBackspace, word.noBackspace);
        }
        dict.noNodes = nodes.size();
        dict.wordNodes = sortedNodes;
        dict.generator = generator;

        return dict;
    }

    private static void solve(Trie root, ArrayList<Trie> words) {
        for (Trie word : words) {
            Trie current = word;
            while (current != root) {
                if (current.letter[26] == null) {
                    current.letter[26] = word;
                }
                current = current.getParent();
            }
        }

        Queue<Trie> q = new LinkedList<>();
        q.add(root);
        root.distance = 0;
        root.noAutoCompletes = 0;
        root.letter[26] = null; // can't autocomplete if no letter typed
        while (q.size() > 0) {
            Trie current = q.poll();
            for (int i = 0; i < 28; i++) {
                Trie next = current.letter[i];
                if (next != null) {
                    int ac = current.noAutoCompletes + (i == 26 ? 1 : 0);
                    int bs = current.noBackspace + (i == 27 ? 1 : 0);
                    if (next.distance == -1 ||
                            (next.distance == current.distance + 1 && next.noAutoCompletes > ac) ||
                            (next.distance == current.distance + 1 && next.noAutoCompletes == ac && next.noBackspace > bs)) {
                        if (next.distance == -1) {
                            q.add(next);
                        }
                        next.distance = current.distance + 1;
                        next.noAutoCompletes = ac;
                        next.noBackspace = bs;
                    }
                }
            }
        }
    }

    private static void randomShuffle(Random random, ArrayList<Trie> words) {
        for (int i = 0; i < words.size(); i++) {
            int j = i + random.nextInt(words.size() - i);
            Trie tmp = words.get(i);
            words.set(i, words.get(j));
            words.set(j, tmp);
        }
    }

    public static class LetterGenerator {
        private Random random;

        private static double relFreq[] = new double[] {
                8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.361, 0.150, 1.974, 0.074
        };

        private char[] letters = new char[4096];

        private static class LetFreq implements Comparable<LetFreq> {
            char c;
            double freq;

            public LetFreq(char c, double freq) {
                this.c = c;
                this.freq = freq;
            }

            @Override
            public int compareTo(LetFreq o) {
                return Double.compare(o.freq, this.freq);
            }
        }

        public char next() {
            return letters[random.nextInt(letters.length)];
        }

        public LetterGenerator(Random r, int n) {
            random = r;
            LetFreq[] freq = new LetFreq[26];
            for (int i = 0; i < 26; i++) {
                freq[i] = new LetFreq((char)('a'+i), relFreq[i]);
            }
            Arrays.sort(freq);
            double sum = 0.0;
            for (int i = 0; i < n; i++) {
                sum += freq[i].freq;
            }
            for (int i = 0; i < letters.length; i++) {
                double d = random.nextDouble() * sum;
                int j = 0;
                while (d >= freq[j].freq) {
                    d -= freq[j].freq;
                    j++;
                }
                assert j < n;
                letters[i] = freq[j].c;
            }
        }
    }

}

// Corner cases to test:
// * You can't autocomplete when no characters typed
// * If you are at a known word and autocomplete, you will autocomplete to that word (if the most common). Clarify this?
// * Simple case where you need to autocomplete twice
// * Simple case where you just type out the word without autocomplete

// * Maximum number of autocompletes (a <tab> a <tab> repeat)
// * Maximum number of autocompletes and backspaces (a <tab> <bs> a <tab> <bs> repeat) or (a <tab> <bs> <tab> <bs> repeat)
// * Dictionary where all words are subsets of each other
// * Solution that is O(N*|A|) where |A| is the number of autocompletes should time out
// * a <tab> <bs> * A LOT if just one better than aaaaa...  (and a case where it's the opposite)
