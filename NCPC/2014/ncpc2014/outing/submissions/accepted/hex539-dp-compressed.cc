#include <algorithm>
#include <iostream>
using namespace std;

/*
 * Author
 *   Robin Lee (hex539)
 *
 * Algorithm
 *   Dynamic programming - dp[m] means we can make 'm' participants.
 *
 * Complexity
 *   O(N^2)
 */

#define MAXN 1000
int dp[MAXN*2+1];
int x[MAXN];

bool active[MAXN];
int depth[MAXN];
int sink[MAXN];

int min_size[MAXN];
int max_size[MAXN];

void dfs(int a){
    active[a]=true;
    int b=x[a];
    sink[a]=a;

    if (active[b]){
        min_size[a]=1+(depth[a]-depth[b]);
    }else{
        if (not depth[b]) depth[b]=depth[a]+1, dfs(b);
        sink[a]=sink[b];
    }

    ++max_size[sink[a]];
    active[a]=false;
}

int main(){
    // read in participants, make connectivity clusters using depth-first search
    int n,m; cin>>n>>m;
    for (int i=0; i<n; i++) cin>>x[i], --x[i];
    for (int i=n; i--;) if (not depth[i]) depth[i]=1, dfs(i);

    // dynamic programming to find legal subset sizes
    dp[0]=1;
    for (int i=0; i<n; i++){
        if (sink[i]==i and max_size[i]){
            for (int j=n; j>=0; --j){
                if (dp[j]) ++dp[j+min_size[i]], --dp[j+max_size[i]+1], --dp[j+1];
            }
            for (int j=1; j<=n+1; j++) dp[j]+=dp[j-1], dp[j-1]=!!dp[j-1];
        }
    }

    int res=m;
    while (not dp[res]) --res;
    cout<<res<<endl;
}
