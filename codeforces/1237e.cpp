#include <bits/stdc++.h>

using namespace std;
const int N = 1e6+10; 
bool is[N];

// if you focus on perfect bst, left-right diff size could be O(n), too much.
//
// key idea is note root = n (mod 2), since right keep eq, and n is right-most
// => right size is even.
// we will show for a valid n, only one shape.
// for depth <2, only 1,2 is.
// then for depth>=2, since right has to be even, we have pattern
// 1 2
// 4 5
// 9 10
// 20 21
// ..
//
// i.e. for depth > 2, left/right same depth, since they are not fullfilled, otherwise not perfect 
void solve() {
    int n; cin >> n;
    is[1]=is[2]=true;
    pair<int, int> p = {1,2};
    while (true) {
        pair<int, int> nxt;
        if (p.first&1) {
            nxt = {p.second*2, p.second*2+1};
        } else {
            nxt = {p.first*2+1, p.second*2};
        }
        p = nxt;
        if (p.first >= N) break;
        is[p.first] = is[p.second] = true;
    }

    cout << (is[n]?1:0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
