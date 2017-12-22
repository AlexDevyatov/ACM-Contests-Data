#include <iostream>
#include <map>
using namespace std;

typedef map<int,int> MII;

const int DELAY = 1000;

int main() {
  int n,k;
  cin >> n >> k;
  MII events;
  for (int i=0;i<n;++i) {
    int x;
    cin >> x;
    events[x]++;
    events[x+DELAY]--;
  }
  int mx=0;
  int cur=0;
  for (auto it : events) {
    cur+=it.second;
    mx=max(mx,cur);
  }
  cout << (mx+k-1)/k << endl;
}
