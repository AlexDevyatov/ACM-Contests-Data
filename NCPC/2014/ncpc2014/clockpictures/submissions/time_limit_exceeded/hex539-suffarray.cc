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
 *   Generate a suffix array for the circular string using the power-of-two
 *   method. Rotate to the lexicographically smallest element and compare
 *   from there.
 *
 * Complexity
 *   O(N log^2 N)
 */

void normalise(basic_string<ll> &s){
    map<ll,ll> renum;
    int cnt=0;
    for (int i=s.length(); i--;) renum[s[i]];
    for (map<ll,ll>::iterator it=renum.begin(); it!=renum.end(); ++it) it->second=cnt++;
    for (int i=s.length(); i--;) s[i]=renum[s[i]];
}

int min_rotation(basic_string<ll> s){
    normalise(s);
    for (int radius=1; radius<=(1<<22); radius<<=1){
        basic_string<ll> t=s;
        for (int i=0; i<s.length(); i++){
            s[i]=(t[i]*t.length()+t[(i+radius)%t.length()]);
        }
        normalise(s);
    }
    for (int i=s.length(); i--;)
        if (not s[i])
            return i;
}

basic_string<ll> read_clock(int n){
    int const modulo = 360000;

    vector<int> v(n);
    for (int i=0; i<n; i++) cin>>v[i];
    sort(v.begin(),v.end());
    v.push_back(v.front());

    basic_string<ll> s;
    for (int i=0; i<n; i++) s+=(v[i+1]-v[i]+modulo)%modulo;
    return (s+s).substr(min_rotation(s), s.length());
}

int main(){
    int n; cin>>n;
    basic_string<ll> a=read_clock(n), b=read_clock(n);
    cout<<(a==b? "possible": "impossible")<<endl;
}
