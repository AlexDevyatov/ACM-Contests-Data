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
 *   Hash each difference string into a single int using a
 *   non-positional algorithm like checksum. Compare for equality.
 *
 * Complexity
 *   O(NlogN)
 */
int const modulo = 360000;

int distance(int a,int b){
  return min(abs(a-b), (abs(a-b)+modulo)%modulo);
}

uint64_t read_clock(int n){
    uint64_t res=0ull, par=0ull;

    vector<int> v(n);
    for (int i=0; i<n; i++) cin>>v[i];
    sort(v.begin(),v.end());

    for (int i=0,j=0; i<n; i++){
      int k=(j+1)%n;
      while (distance(v[i],v[k]) >= distance(v[i],v[j])) j=k++, k%=n;
      res=max(res,uint64_t(distance(v[i],v[j])));
      par=par xor ((v[(i+1)%n]-v[i]+modulo)%modulo);
    }

    return res xor (par<<32ull);
}

int main(){
    int n; cin>>n;
    cout<<(read_clock(n)==read_clock(n)? "possible": "impossible")<<endl;
}
