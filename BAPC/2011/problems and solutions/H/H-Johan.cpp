//Judge Solution for Walking the Plank, BAPC 2011

//Johan de Ruiter

#include <iostream>
#include <sstream>  
#include <cstring>
#include <vector>  
#include <queue>  
#include <set>  
#include <map>  
#include <cstdio>  
#include <cstdlib>  
#include <cctype>  
#include <cmath>  
#include <list>  
#include <numeric> 
#include <ctime>
#include <algorithm>
using namespace std;  
  
const int PIRATE_SIDE=0, COMMERCIAL_SIDE=1;

struct pirate
{
  int t[4], side;
  long long arrival;
};

bool operator<(const pirate &a, const pirate &b)
{
  if(a.arrival!=b.arrival)
    return a.arrival>b.arrival;

  return a.t[3-2*a.side]<b.t[3-2*b.side];
}

long long arrival(const pirate &p){ return max(0ll,p.arrival); }

int main()
{
  int run,runs,N,P;
  scanf("%d",&runs);
  for(run=0;run<runs;run++)
  {
    priority_queue<pirate> plank[2];
    scanf("%d %d",&N,&P);
    pirate p; p.side=PIRATE_SIDE;
    for(int j=0;j<P;j++){
      p.arrival=-P+j; //for initial order, treat as zero
      scanf("%d %d %d %d",&p.t[0],&p.t[1],&p.t[2],&p.t[3]);
      plank[PIRATE_SIDE].push(p);
    }

    int departCount[2]={0,0}; //pirates out and in
    long long plankAvailable=0;

    while(departCount[COMMERCIAL_SIDE]!=N)
    {
      int turn=!(departCount[PIRATE_SIDE]<N&&(plank[COMMERCIAL_SIDE].empty()||
               (arrival(plank[COMMERCIAL_SIDE].top())>plankAvailable&&
               !plank[PIRATE_SIDE].empty()&&
               arrival(plank[PIRATE_SIDE].top())<arrival(plank[COMMERCIAL_SIDE].top()))));

      p=plank[turn].top();
      plank[turn].pop();
      
      plankAvailable=max(plankAvailable,arrival(p))+p.t[p.side*2];
      p.arrival=plankAvailable+p.t[p.side*2+1];

      departCount[p.side]++;
      p.side=1-p.side;
      plank[p.side].push(p);
    }

    printf("%lld\n",plankAvailable);
  }

  return 0;
}
