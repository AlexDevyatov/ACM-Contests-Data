#include <iostream>
#include <fstream>
using namespace std;

int t,u,d,l,r; // orientation of the die
void rollx( int m)
 { /*m= m%4;*/ if (m<0) m=m+4; for(int k=0; k<m;k++) {r=t;t=l;l=7-r;} }
void rolly( int m)
 { /*m= m%4;*/ if (m<0) m=m+4; for(int k=0; k<m;k++) {u=t;t=d;d=7-u;} }

int main()
{ 
  int nruns;
  cin >> nruns;
  for(int nr =0; nr < nruns; nr++)
  {
    int x,y,times, sign; bool digs; char ch;
    t=1; l=3; d=2; r=4; u=5; // initial orientation
    x=0; y=0; sign=1; times=1; digs=false;

    cin >> ch;
    while (ch != '.') 
    { switch (ch)
      { case '+' :sign= 1; break;
        case '-' :sign=-1; break;
        case 'X' :x = x+sign*times; rollx(sign*times);
                  digs = false; times = 1;      break;
        case 'Y' :y = y+sign*times; rolly(sign*times);
                  digs = false; times = 1;      break;
 
        case '0': case '1': case '2': case '3': case '4': 
        case '9': case '8': case '7': case '6': case '5':
                  if (!digs){digs=true; times=0;}
                  times = 10*times + (ch - '0');  break;
        default : cout << "fuck you! " << endl; ch = '.';
      }
      cin >> ch;
    }
    cout << "position (" 
            << x << "," << y << "), " << t << " dots" << "\n";

  }
  return 0;  
}
