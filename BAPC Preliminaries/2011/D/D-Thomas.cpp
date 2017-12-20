// Polly wants a cracker
// Solution by Thomas Beuman

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> Original, Spoken;
int Edits[8][8]; // Number of edits needed to go from spoken word to original word

int Match[8]; // The original word matching the spoken word

// Splits the sentence into words
vector<string> split (string s)
{ vector<string> vs;
  unsigned int i, j;
  for (i = j = 0; j >= 0 && j < s.size(); i = j+1)
  { j = s.find(' ', i);
    vs.push_back(s.substr(i, j-i));
  }
  return vs;
}

int EditsDP[5001][5001]; // EditsDP[i][j] = number of edits needed to turn prefix i of s into prefix j of t

// Computes minimum number of edits needed to turn string s into string t (using DP)
int edits (string s, string t)
{ int ns = s.size(), nt = t.size(), i, j;
  for (i = 0; i <= ns; i++)
    for (j = 0; j <= nt; j++)
    { if (i == 0)
        EditsDP[0][j] = j;
      else if (j == 0)
        EditsDP[i][0] = i;
      else // Change s[i-1] into t[j-1] (if needed), remove s[i-1] or add t[j-1]
        EditsDP[i][j] = min(EditsDP[i-1][j-1] + (s[i-1] == t[j-1] ? 0 : 1), min(EditsDP[i-1][j] + 1, EditsDP[i][j-1] + 1));
    }
  return EditsDP[ns][nt];
}

int main()
{ int runs, run, n, m, i, j, best, tot;
  string s1, s2;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { getline(cin, s1, '\n');
    getline(cin, s2, '\n');
    Original = split(s1);
    Spoken = split(s2);
    n = Original.size();
    m = Spoken.size();
    // Determine all edit distances
    for (i = 0; i < m; i++)
      for (j = 0; j < n; j++)
        Edits[i][j] = edits(Spoken[i], Original[j]);
    best = 9999;
    for (i = 0; i < n; i++)
      Match[i] = i;
    // Try all permutations of 1..n
    do
    { tot = 0;
      for (i = 0; i < m; i++)
        tot += Edits[i][Match[i]];
      best = min(best, tot);
    }
    while (next_permutation(Match, Match+n));
    printf("%d\n", best);
  }
  return 0;
}
