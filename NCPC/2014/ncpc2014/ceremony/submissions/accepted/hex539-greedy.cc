#include <algorithm>
#include <iostream>
#include <deque>
using namespace std;

/*
 * Author
 *   Robin Lee (hex539)
 *
 * Algorithm
 *   Greedy - remove either the lowest floor or the tallest building,
 *   whichever eliminates more cells.
 */

int main(){
    int n; cin>>n;

    deque<int> h(n);
    for (int i=n; i--;) cin>>h[i];
    sort(h.begin(), h.end());

    int floors=0;
    int buildings=0;

    while (not h.empty()){
        int width = h.size();
        int height = h.back() - floors;

        if (width >= height){
            ++floors;
            while (not h.empty() and h.front() - floors <= 0){
                h.pop_front();
            }
        }else{
            ++buildings;
            h.pop_back();
        }
    }

    cout<<floors+buildings<<endl;
}
