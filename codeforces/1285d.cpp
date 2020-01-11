#include <bits/stdc++.h>

using namespace std;

const int L = 30;
set<int> trk[L];
// think the tree/trie, two-branch implies must 1, one-branch implies 0. reccursive might easier?
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
        for (int i = 0; i < L; i++) {
            trk[i].insert(x>>i);
        }
    }
    int mi = 1<<30;
    for (int x: a) {
        int r = 0;
        for (int i = 0; i < L; i++) {
            if (trk[i].find((x>>i)^1) != trk[i].end()) r |= 1<<i;
        }
        mi = min(mi, r);
    }
    cout << mi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
