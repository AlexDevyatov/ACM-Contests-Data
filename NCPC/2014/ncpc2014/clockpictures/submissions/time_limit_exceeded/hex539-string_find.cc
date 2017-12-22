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
 *   latter and running an implementation of strstr(). The difference from a
 *   correct solution is that this one uses basic_string::find, which is O(MN)
 *   in the worst case.
 *
 * Complexity
 *   O(N^2)
 */

basic_string<int> read_clock(int n){
    int const modulo = 360000;

    vector<int> v(n);
    for (int i=0; i<n; i++) cin>>v[i];
    sort(v.begin(),v.end());
    v.push_back(v.front());

    basic_string<int> s;
    for (int i=0; i<n; i++) s+=(v[i+1]-v[i]+modulo)%modulo;
    return s;
}

int main(){
    int n; cin>>n;
    basic_string<int> a=read_clock(n), b=read_clock(n);
    cout<<((b+b).find(a) != string::npos? "possible": "impossible")<<endl;
}

