#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> v(N);
    multimap<int,int> requests;
    for (int &x : v) cin >> x;
    int m = 0;
    for (const int r_t : v) {
        for (auto it = requests.cbegin(); it != requests.cend();) {
            const int last = it->first; 
            const int left = it->second;
            const int diff = r_t - last;
            requests.erase(it++);
            if (left - diff > 0) { 
                requests.insert(make_pair(r_t, left - diff));
            }
        }
        requests.insert(make_pair(r_t, 1000));
        m = max(m, ((int)requests.size() + K - 1) / K);
    }
    cout << m << endl;
}
