#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

/*
 * Author
 *   Robin Lee (hex539)
 */

int main(){
    int n; cin>>n;

    vector<int> h(n);
    for (int i=n; i--;) cin>>h[i];
    int res=n;

    for (auto i: set<int>(h.begin(),h.end())){
        if (i>=n) continue;

        int cost=i;
        for (auto j: h){
            if (j>i) ++cost;
        }
        res=min(res,cost);
    }

    cout<<res<<endl;
}
