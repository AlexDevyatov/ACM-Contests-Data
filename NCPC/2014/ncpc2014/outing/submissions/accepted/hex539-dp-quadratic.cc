#include <algorithm>
#include <iostream>
#include <cstdint>
#include <deque>
using namespace std;

/*
 * Author
 *   Robin Lee (hex539)
 *
 * Algorithm
 *   Dynamic programming - dp[n][m] means we can make 'm' participants
 *   using the first 'n' clusters.
 *
 * Complexity
 *   O(N^2)
 */

int16_t dp[1024][2048];
struct participant {int16_t x,p,r;} v[1024];

int findroot(int a){
    return v[a].p==a? a: v[a].p=findroot(v[a].p);
}

void join(int a,int b){
    if ((a=findroot(a))==(b=findroot(b))) return;
    if (v[a].r<v[b].r) swap(a,b);
    ++v[v[b].p=a].r;
}

int get_core_size(int a){
    int b=a, res=0;
    do a=v[a].x, b=v[v[b].x].x; while (a^b);
    do a=v[a].x, ++res; while (a^b);
    return res;
}

int main(){
    // read in participants, make connectivity clusters using union-find
    int n,m; cin>>n>>m;
    for (int i=0; i<n; i++) cin>>v[i].x, --v[i].x, v[i].p=i;
    for (int i=n; i--;) join(i,v[i].x);

    // count largest sizes for each cluster and smallest sizes via tortoise/hare algorithm
    vector<pair<int,int>> size(n);
    for (int i=n; i--;) ++size[findroot(i)].second;
    for (int i=n; i--;) if (i==findroot(i)) size[i].first=get_core_size(i);

    // dynamic programming to find legal subset sizes
    dp[0][0]=1;
    for (int i=0; i<n; i++){
        for (int j=0; j<=n; j++){
            if (dp[i][j]){
                ++dp[i+1][j+size[i].first+0];
                --dp[i+1][j+size[i].second+1];
                ++dp[i+1][j+0];
                --dp[i+1][j+1];
            }
            dp[i+1][j+1]+=dp[i+1][j];
        }
    }

    int res=m;
    while (not dp[n][res]) --res;
    cout<<res<<endl;
}
