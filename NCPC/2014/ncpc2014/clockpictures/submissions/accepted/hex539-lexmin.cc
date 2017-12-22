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
 *   Lyndon factorisation identifies the minimum rotation of each clock's
 *   difference string and then checks if the two are identical.
 */

template <class T> int factorise(basic_string<T> s){
    s+=s;

    int k=0;
    for (int i=1,j=0; i<s.size(); i++){
        if (s[i]>s[j]){
            j=k;
        }else if (s[i]<s[j]){
          while(k<=j) k+=(i-j); // Marc changed this
            i=j=k;
        }else{
            ++j;
        }
    }
    return k%(s.size()/2);
}

basic_string<int> read_clock(int n){
    int const modulo = 360000;

    vector<int> v(n);
    for (int i=0; i<n; i++) cin>>v[i];
    sort(v.begin(),v.end());
    v.push_back(v.front()+modulo);

    basic_string<int> s;
    for (int i=0; i<n; i++) s+=(v[i+1]-v[i])%modulo;
    return (s+s).substr(factorise(s), s.length());
}

int main(){
    int n; cin>>n;
    basic_string<int> a=read_clock(n), b=read_clock(n);
    cout<<(a==b? "possible": "impossible")<<endl;
}
