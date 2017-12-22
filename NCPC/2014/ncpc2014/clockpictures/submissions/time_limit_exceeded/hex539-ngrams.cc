#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

/*
 * Author
 *   Robin Lee (hex539)
 *
 * Algorithm
 *   Convert each 16-gram to a letter representation using a suffix array-like
 *   algorithm. Run straightfoward brute-force comparison from there.
 *
 * Complexity
 *   O(N^2)
 */

#define MAXN 200000

void normalise(basic_string<ll> &s){
    static ll renum[MAXN];
    for (int i=s.length(); i--;) renum[i]=s[i];
    sort(renum,renum+s.size());
    for (auto &i: s) i=lower_bound(renum,renum+s.size(),i)-renum;
}

basic_string<ll> &simplify(basic_string<ll> &s){
    normalise(s);
    for (int radius=1; radius<=(1<<3); radius<<=1){
        basic_string<ll> t=s;
        for (int i=0; i<s.length(); i++){
            s[i]=(t[i]*t.length()+t[(i+radius)%t.length()]);
        }
        normalise(s);
    }
    return s;
}

basic_string<ll> read_clock(int n){
    int const modulo = 360000;

    vector<int> v(n);
    for (int i=0; i<n; i++) cin>>v[i];
    sort(v.begin(),v.end());
    v.push_back(v.front());

    basic_string<ll> s;
    for (int i=0; i<n; i++) s+=(v[i+1]-v[i]+modulo)%modulo;
    return simplify(s);
}

int main(){
    int n; cin>>n;
    basic_string<ll> a=read_clock(n), b=read_clock(n);
    cout<<(~(a+a).find(b)? "possible": "impossible")<<endl;
}
