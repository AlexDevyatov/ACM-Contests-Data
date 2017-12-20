#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define DBGDO(X) cerr << #X << " = " << (X) << endl

struct Carpet {
    int count;
    int w;
    int h;
};

int rw, rh;
int cnt;
Carpet cps[120];

bool room[500][500];

bool tryfill(int x, int y) {
    /*
     * imagine the room:
     *        x
     *   ------>
     *  |
     *  |
     * y|
     *  V
     *
     *  the (x,y) is the topmost (and among those the leftmost) free cell
     */
    // wrap lines around
    if (x >= rw) return tryfill(0,y+1);
    // if we left the room already there is nothing left to fill
    if (y >= rh) return true;
    // if cell was lift already go to next one
    if (room[x][y] == true) return tryfill(x+1, y);
    // for any carpet
    FOR (c, 0, cnt) if (cps[c].count > 0) {
        Carpet* cur = cps + c;
        int curw = cur->w;
        int curh = cur->h;
        // in any rotation
        FOR (asdf,0,2) {
            swap(curw,curh);
            // check that it does not leave the room boundaries
            if (x + curw > rw) continue;
            if (y + curh > rh) continue;
            bool allfree = true;
            // check that the occupied cells aren't occupied already by other carpets
            FOR (cx, x, curw + x) {
                if (!allfree) break;
                FOR (cy, y, y+1) {
                    if (room[cx][cy] == true) {
                        allfree = false;
                        break;
                    }
                }
            }
            if (!allfree) continue;
            // if all are still free, place carpet
            cur->count--;
            FOR (cx, x, curw + x) FOR (cy, y, curh + y) {
                    assert(room[cx][cy] == false);
                    room[cx][cy] = true;
            }
            // continue filling
            if (tryfill(x+curw,y))
                return true;
            // if it failed, move carpet back to stock
            cur->count++;
            FOR (cx, x, curw + x) FOR (cy, y, curh + y) {
                    assert(room[cx][cy] == true);
                    room[cx][cy] = false;
            }
            // don't try the other rotation for squares
            if (curw == curh) break;
        }
    }
    return false;
}

int main() {
    cin >> rw >> rh;
    cin >> cnt;
    int A = 0;
    FOR (i,0,cnt) {
        cin >> cps[i].count >> cps[i].w >> cps[i].h;
        A += cps[i].count * cps[i].w * cps[i].h;
    }
    FOR (i, 0, rw) FOR (j, 0, rh) {
        room[i][j] = false;
    }
    if (A >= rw*rh && tryfill(0,0)) cout << "yes" << endl;
    else cout << "no" << endl;
    return 0;
}
