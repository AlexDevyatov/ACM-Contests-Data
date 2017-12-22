#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> v(N);
    vector<pair<int,int>> requests;
    for (int &x : v) cin >> x;
    int m = 0;
    for (const int r_t : v) {
        for (int i = 0; i < requests.size(); ++i) {
            auto &p = requests[i];
            const int d = r_t - p.first;
            p.second -= d;
            p.first = r_t;
            if (p.second <= 0) { 
                swap(requests[i], requests[requests.size()-1]);
                requests.erase(requests.begin() + requests.size() - 1);
                --i;
            }
        }
        requests.push_back(make_pair(r_t, 1000));
        m = max(m, ((int)requests.size() + K - 1) / K);
    }
    cout << m << endl;
}
