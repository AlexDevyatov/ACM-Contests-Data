#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN 1000
typedef int intn[MAXN+1];
intn dp,x,active,depth,sink,min_size,max_size;

void dfs(int a){
    active[sink[a]=a]=1;
    if (active[x[a]]){
        min_size[a]=1+(depth[a]-depth[x[a]]);
    }else{
        if (not depth[x[a]]) depth[x[a]]=depth[a]+1, dfs(x[a]);
        sink[a]=sink[x[a]];
    }
    ++max_size[sink[a]];
    active[a]=0;
}

int main(){
    int n,m; cin>>n>>m;
    for (int i=0; i<n; i++) cin>>x[i], --x[i];
    for (int i=n; i--;) if (not depth[i]) depth[i]=1, dfs(i);

    dp[0]=1;
    for (int i=0; i<n; i++)
        if (sink[i]==i and max_size[i])
            for (int j=n; j>=0; --j)
                if (dp[j]) dp[j+min_size[i]]=dp[j+max_size[i]]=1;

    int res=m;
    while (not dp[res]) --res;
    cout<<res<<endl;
}
