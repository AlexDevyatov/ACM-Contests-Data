#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
using namespace std;

/*
 * Author
 *   Robin Lee (hex539)
 *
 * Algorithm
 *   Run a rolling hash over the whole clock's difference string and take
 *   the minimum of that.
 *
 * Complexity
 *   O(NlogN)
 */

template <class T> uint64_t hash_str(basic_string<T> s,uint64_t mul,uint64_t mod){
    mod = (mod % (1llu<<30llu)) + 77;
    mul = (mul % (mod - 5)) + 2;

    vector<uint64_t> power(s.length()+1, 1);
    for (int i=1; i<=s.length(); i++) power[i]=(power[i-1]*mul)%mod;

    uint64_t hash_str=0;
    for (int i=0; i<s.length(); i++){
        (hash_str+=(    power[s.length()-1-i])*s[i])%=mod;
    }
    uint64_t res=~0llu;
    for (int i=0; i<s.length(); i++){
        (hash_str*=mul)%=mod;
        (hash_str+=(mod-power[s.length()]+1)*s[i])%=mod;
        res=min(res,hash_str);
    }
    return res;
}

uint64_t read_clock(int n){
    int const modulo = 360000;

    vector<int> v(n);
    for (int i=0; i<n; i++) cin>>v[i];
    sort(v.begin(),v.end());

    static int param[4][2]={};
    while (not param[0][0]){
      for (int i=4; i--;) for (int j=2; j--;) param[i][j]=rand();
    }

    basic_string<uint64_t> s;
    for (int i=0; i<n; i++) s+=(v[(i+1)%n]-v[i]+modulo)%modulo;
    return hash_str(s, param[0][0], param[0][1])
       xor hash_str(s, param[1][0], param[1][1])
       xor hash_str(s, param[2][0], param[2][1])
       xor hash_str(s, param[3][0], param[3][1]);
}

int main(){
    int n; cin>>n;
    cout<<(read_clock(n)==read_clock(n)? "possible": "impossible")<<endl;
}
