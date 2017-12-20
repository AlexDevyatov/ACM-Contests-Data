// Rolling Dice
// Solution by Thomas Beuman

#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

int main()
{ int runs, run, n, i, j, x, y, top, front, left, newtop, newfront, newleft, sign, factor, dir;
  int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
  string s;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { getline(cin, s, '\n');
    x = y = 0;
    // Initial configuration of the die:
    top = 1;   // Top side
    front = 2; // Facing south
    left = 3;  // Facing west
    sign = 1; // -1 for reversed directions
    factor = -1; // -1 represents "no factor"
    n = s.size();
    for (i = 0; i < n; i++)
    { if (s[i] == '+')
        sign = 1;
      else if (s[i] == '-')
        sign = -1;
      else if (s[i] >= '0' && s[i] <= '9')
        factor = (factor < 0 ? 0 : 10 * factor) + (s[i]-'0');
      else if (s[i] == 'X' || s[i] == 'Y')
      { if (factor < 0) // No factor
          factor = 1;
        dir = ('Y' - s[i]) + (1 - sign);
        x += factor * dx[dir];
        y += factor * dy[dir];
        for (j = 0; j < factor % 4; j++)
        { switch (dir)
          { case 0: // North
              newtop = front;
              newfront = 7 - top;
              newleft = left;
              break;
            case 1: // East
              newtop = left;
              newfront = front;
              newleft = 7 - top;
              break;
            case 2: // South
              newtop = 7 - front;
              newfront = top;
              newleft = left;
              break;
            case 3: // West
              newtop = 7 - left;
              newfront = front;
              newleft = top;
              break;
            default:
              printf("Something's wrong!\n");
              newtop = newfront = newleft = 0;
          }
          top = newtop;
          front = newfront;
          left = newleft;
        }
        factor = -1; // Reset factor
      }
      else if (s[i] == '.')
        break;
      else
        printf("Something's wrong!\n");
    }
    printf("position (%d,%d), %d dots\n", x, y, top);
  }
  return 0;
}
