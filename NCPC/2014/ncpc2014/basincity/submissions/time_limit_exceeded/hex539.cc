#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

#define MAXN 100000
vector<int> edge[MAXN];
vector<int> active;
int used[MAXN];
int dead[MAXN];
int k,n;

bool solve(){
  if (k<=0) return true;

  vector<int> will;
  while (not active.empty()){
    swap(active.back(),active[rand()%active.size()]);
    int x=active.back();
    active.pop_back();
    will.push_back(x);

    if (not dead[x]){
      --k;
      ++used[x];
      for (auto y: edge[x]) ++dead[y];
      if (solve()) return true;
      for (auto y: edge[x]) --dead[y];
      --used[x];
      ++k;
    }
  }
  for (auto i: will) active.push_back(i);

  return false;
}

int card[MAXN];

void remove(int x){
  ++dead[x];
  ++used[x];
  --k;

  vector<int> frontier;
  for (int y: edge[x])
    if (not dead[y]){
      frontier.push_back(y);
      ++dead[y];
      --card[y];
    }
  for (int y: frontier)
    for (int z: edge[y])
      if (not dead[z] and 1>=--card[z])
        remove(z);
}

int main(){
  srand(0x539);

  cin>>k>>n;
  for (int i=0; i<n; i++){
    cin>>card[i];
    active.push_back(i);
    for (int j=0; j<card[i]; j++){
      int x; cin>>x; edge[i].push_back(--x);
    }
  }

  for (int i=n; i--;)
    if (card[i]<=1 and not dead[i])
      remove(i);
  for (int i=0; i<active.size(); i++)
    if (dead[active[i]])
      swap(active[i],active.back()), active.pop_back();

  cout<<(solve()?"possible":"impossible")<<endl;
}
