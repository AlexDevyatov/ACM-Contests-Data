#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

/**
 * Author
 *   Robin Lee (hex539)
 *
 * Solution
 *   Dynamic programming with state as last car in each direction and function as
 *   a tuple of (#satisfied, total time). This is incorrect because sometimes we
 *   may want to sacrifice earlier cars in exchange for a smaller backlog.
 *
 * Complexity
 *   O(N^2)
 */

// dp[carA_last][carB_last] => {score, min_time}
#define MAXN 254
pair<int,int> dp[MAXN+2][MAXN+2];

struct Car{
  int start;
  int end;
  int dir;
} car[MAXN+2];
int nxt[MAXN+2][2];

int main(){
  memset(nxt,-1,sizeof nxt);
  memset(dp,-1,sizeof dp);
  dp[0][0]=make_pair(0,0);

  int t,n; cin>>t>>n;
  for (int i=0; i<=n; i++){
    if (i<n){
      char dirn;
      cin>>dirn>>car[i].start>>car[i].end;
      car[i].dir=(dirn=='E');
      car[i].end+=car[i].start;
    } else car[i]={1<<28, 1<<28, 0};
  }
  for (int i=n+1; i-->1;){
    for (int j=2; j--;) nxt[i-1][j]=(j==car[i].dir?i:nxt[i][j]);
  }

  int res=0;

  for (int i=0; i<=n; i++){
    for (int j=0; j<=n; j++){
      if (!~dp[i][j].first) continue;
      res=max(res,dp[i][j].first);
      { int k=nxt[i][+car[i].dir];
        if (!~k) break;
        dp[k][j]=max(dp[k][j], make_pair(dp[i][j].first+(-dp[i][j].second<=car[i].end),
                                         -max(-dp[i][j].second, car[i].start)-3));
      }
      { int k=nxt[j][!car[i].dir];
        if (!~k) break;
        dp[k][i]=max(dp[k][i], make_pair(dp[i][j].first+(-dp[i][j].second<=car[i].end),
                                         -max(-dp[i][j].second, car[i].start)-t));
      } 
    }
  }

  cout<<n-res<<endl;
}
