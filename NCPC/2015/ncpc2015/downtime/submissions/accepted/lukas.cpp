#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

int main()
{
  int n, k; scanf("%d %d", &n, &k);
  queue<int> q;
  size_t res = 0;
  rep(i,0,n)
  {
    int x; scanf("%d", &x);
    q.push(x);
    while (q.front() <= q.back() - 1000) q.pop();
    res = max(res, (q.size() + k - 1) / k);
  }
  cout << res << endl;
}
