#include <algorithm>
#include <iostream>
#include <cstdint>
#include <cstring>
#include <vector>
using namespace std;

/**
 * Author
 *   Robin Lee (hex539)
 *
 * Solution
 *   Dynamic programming with state as last car in each direction plus the number
 *   satisfied so far and function as minimum time taken.
 *
 * Complexity
 *   O(N^3)
 */

#define MAXN 800
uint32_t dp[2][2][MAXN/2+1][MAXN+1];
void up(uint32_t &x,uint32_t y){if (y<x) x=y;}

struct Car{
  uint32_t start;
  uint32_t end;
  bool dir;
};

vector<Car> a,b;

int main(){
  int t,n; cin>>t>>n;
  for (int i=0; i<n; i++){
    if (i<n){
      char dirn;
      Car c; cin>>dirn>>c.start>>c.end;
      c.end+=c.start;
      c.dir=(dirn=='E');
      (dirn=='E'? a: b).push_back(c);
    }
  }
  if (a.size()<b.size()) swap(a,b);

  int res=0;

  memset(dp,-1,sizeof dp);
  if (not a.empty()) dp[1][0][0][1]=a[0].start;
  if (not b.empty()) dp[0][1][1][1]=b[0].start;

  for (int i=0; i<=a.size(); i++){
    for (int j=0; j<=b.size(); j++){
      for (int k=0; k<=i+j; k++){
        for (int z=0; z<2; z++){
          if (!~dp[1&i][z][j][k]) continue;
          res=max(res,k);

          if (i<a.size()){
            uint32_t when=max(a[i].start, dp[1&i][z][j][k] + (z==0? 3: t));
            up(dp[1&~i][0][j][k+0], when);
            if (when <= a[i].end){
              up(dp[1&~i][0][j][k+1], when);
            }
          }
          if (j<b.size()){
            uint32_t when=max(b[j].start, dp[1&i][z][j][k] + (z==1? 3: t));
            up(dp[1&+i][1][j+1][k+0], when);
            if (when <= b[j].end){
              up(dp[1&+i][1][j+1][k+1], when);
            }
          }
        }
      }
    }

    for (int j=0; j<=b.size(); j++)
      for (int k=0; k<=i+j; k++)
        for (int z=0; z<2; z++)
          dp[1&i][z][j][k]=-1u;
  }

  cout<<n-res<<endl;
}
