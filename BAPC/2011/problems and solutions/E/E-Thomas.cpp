// Undercover Pirate
// Solution by Thomas Beuman

#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

#define pii pair<int, int>
#define mpii make_pair<int, int>
#define last second

const pii zero = mpii(1, 0); // Empty range

pii left_range1, left_range2, right_range1, right_range2; // The ranges put on either side of the scale

int sz (pii range)
{ return range.last - range.first + 1;
}

void printrange (pii range, bool space_after)
{ if (sz(range) > 0)
  { if (!space_after)
      printf(" ");
    if (sz(range) == 1)
      printf("%d", range.first);
    else
      printf("%d-%d", range.first, range.last);
    if (space_after)
      printf(" ");
  }
}

char weigh()
{ printrange(left_range1, true);
  printrange(left_range2, true);
  printf("+");
  printrange(right_range1, false);
  printrange(right_range2, false);
  printf("\n");
  fflush(NULL);
  char res;
  scanf("\n%c", &res);
  return res;
}

int main()
{ int runs, run, N, n, n1, n2, k1, k2;
  int uwf, nlf, nhf, certain_ninja, pirate;
  bool heavy;
  pii unknown_weight, not_lighter, not_heavier;
  // The ranges containing all ninja's whose weight we know nothing about,
  // those who are certain to be not lighter, and those who are certain not to be heavier
  char res;
  scanf("%d", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d", &N);
    unknown_weight = mpii(1, N); // All ninja's are of unknown weight
    not_lighter = not_heavier = zero; // Empty
    certain_ninja = 0; // A ninja of whom we know he is not the pirate
    do
    { // There are only ninja's of unknown weight
      // Put one third of the ninja's (rounded down) on the side, distribute the rest over the two sides of the scale
      // Use the certain ninja to equal the numbers (if there is a mismatch and there is a certain ninja)
      n = sz(unknown_weight);
      k1 = (n+1)/3; // Number of ninja's on the left scale
      k2 = (n+2)/3; // On the right
      if (k2 > k1 && certain_ninja == 0) // There is a mismatch but no certain ninja (first use of the scale)
        k2 = k1;
      uwf = unknown_weight.first;
      left_range1 = mpii(uwf, uwf + k1-1);
      left_range2 = (k2 > k1 ? mpii(certain_ninja, certain_ninja) : zero);
      right_range1 = mpii(uwf + k1, uwf + k1 + k2-1);
      right_range2 = zero;
      res = weigh();
      if (res == 'E') // The ninja's left off constitute the new set of ninja's of unknown weight
      { unknown_weight.first = uwf + k1 + k2;
        certain_ninja = uwf;
      }
      else
      { unknown_weight = zero;
        // Assuming result is 'L' for the moment
        not_lighter = left_range1;
        not_heavier = right_range1;
        if (certain_ninja == 0) // Is necessary, otherwise it goes wrong for n == 2
          certain_ninja = uwf + k1 + k2;
        if (res == 'R')
          swap(not_lighter, not_heavier);
      }
    }
    while (res == 'E');
    // Now some are known to be not lighter, some are not heavier
    while (sz(not_lighter) + sz(not_heavier) != 1)
    { n1 = sz(not_lighter);
      n2 = sz(not_heavier);
      if (n1 == 1 && n2 == 1) // Special case: one of either "type"
      { // Put the not-lighter ninja up against the certain ninja
        left_range1 = not_lighter;
        right_range1 = mpii(certain_ninja, certain_ninja);
        left_range2 = right_range2 = zero;
        res = weigh();
        if (res == 'E') // The not-lighter ninja is certain to be a ninja
          not_lighter = zero;
        else // The not-heavier ninja is certain to be a ninja
          not_heavier = zero;
      }
      else // There are at least two ninja's of the same "type"
      { // Put one third on each side of the scale
        // Put equal numbers of both types (k1 and k2) on each side
        k1 = min(n1/2, (n1+n2+1)/3); // Use as many not-lighter ninja's as possible
        k2 = (n1+n2+1)/3 - k1; // Add not-heavier ninja's
        nlf = not_lighter.first;
        nhf = not_heavier.first;
        left_range1 = mpii(nlf, nlf + k1-1);
        left_range2 = mpii(nhf, nhf + k2-1);
        right_range1 = mpii(nlf + k1, nlf + 2*k1-1);
        right_range2 = mpii(nhf + k2, nhf + 2*k2-1);
        res = weigh();
        if (res == 'E')
        { not_lighter.first = nlf + 2*k1;
          not_heavier.first = nhf + 2*k2;
        }
        else if (res == 'L')
        { not_lighter = left_range1;
          not_heavier = right_range2;
        }
        else if (res == 'R')
        { not_lighter = right_range1;
          not_heavier = left_range2;
        }
      }
    }
    heavy = (sz(not_lighter) == 1);
    pirate = (heavy ? not_lighter.first : not_heavier.first);
    printf("Ninja %d is a %s pirate\n", pirate, heavy ? "heavy" : "light");
    fflush(NULL);
  }
  return 0;
}
