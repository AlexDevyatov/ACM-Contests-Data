#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> sweep(101005);
    for (int i = 0; i < N; ++i) {
        int cur;
        cin >> cur;
        sweep[cur] += 1;
        sweep[cur+1000] -= 1;
    }
    int top = 0;
    int active = 0;
    for (int i = 0; i < 101005; ++i) {
        active += sweep[i];
        top = max(top, active);
    }
    assert(active == 0);
    cout << ((top + K - 1) / K) << endl;
}
