#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
 * Author
 *   Robin Lee (hex539)
 *
 * Algorithm
 *   Search for one clock's difference string in the other by duplicating the
 *   latter and running an implementation of strstr(). Because keys are integers
 *   we have to implement KMP for ourselves.
 *
 *   (teams who don't know KMP could also have converted each difference to a unique
 *    string representation, for example base64 encoding, and then concatenated all
 *    of them to run strstr() in - glibc seems to use KMP for large strings)
 *
 * Complexity
 *   O(NlogN)
 */

typedef vector<int> vi;
typedef basic_string<int> bi;

bool strstr_circular(bi needle,bi haystack){
    haystack+=haystack;

    vi kmp(needle.length());
    for (int i=2; i<needle.length(); i++){
      for (kmp[i]=kmp[i-1]; kmp[i] and needle[kmp[i]]!=needle[i-1]; kmp[i]=kmp[kmp[i]]);
      if (needle[kmp[i]]==needle[i-1]) ++kmp[i];
    }

    int state=0;
    for (auto const c: haystack) {
        while (state and c!=needle[state]) state=kmp[state];
        if (c==needle[state] and needle.length()==++state) return true;
    }
    return false;
}

basic_string<int> read_clock(int n){
    int const modulo = 360000;

    vi v(n);
    for (int i=0; i<n; i++) cin>>v[i];
    sort(v.begin(),v.end());
    v.push_back(v.front()+modulo);

    bi s;
    for (int i=0; i<n; i++) s+=(v[i+1]-v[i])%modulo;
    return s;
}

int main(){
    int n; cin>>n;
    auto a=read_clock(n), b=read_clock(n);
    cout<<(strstr_circular(a,b)? "possible": "impossible")<<endl;
}

