#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
 * Author
 *   Robin Lee (hex539)
 *
 * Algorithm
 *   Backtracking on whether to use each cluster of participants
 *   - times out because there can be up to 1000 clusters.
 *
 * Complexity
 *   O(2^N)
 */

#define MAXN 1000
int min_size[MAXN];
int max_size[MAXN];
int x[MAXN];

void dfs(int a,int p=-1){
    static bool active[MAXN];
    static int depth[MAXN];
    static int sink[MAXN];

    if (not depth[a]) depth[a]=1;
    else if (!~p) return;

    active[a]=true;
    int b=x[a];
    sink[a]=a;

    if (active[b]){
        min_size[a]=1+(depth[a]-depth[b]);
    }else{
        if (not depth[b]) depth[b]=depth[a]+1, dfs(b,a);
        sink[a]=sink[b];
    }

    ++max_size[sink[a]];
    active[a]=false;
}

int solve(int n,int m,int slack=0){
    if (n<=0){
        return max(0, m-slack);
    }

    int res=min(m, solve(n-1,m,slack));
    if (min_size[n-1] and m>=min_size[n-1]){
        res=min(res, solve(n-1,m-min_size[n-1], slack+max_size[n-1]-min_size[n-1]));
    }
    return res;
}

int main(){
    // read in participants, make connectivity clusters using depth-first search
    int n,m; cin>>n>>m;
    for (int i=0; i<n; i++) cin>>x[i], --x[i];
    for (int i=n; i--;) dfs(i);
    cout<<m-solve(n,m)<<endl;
}
