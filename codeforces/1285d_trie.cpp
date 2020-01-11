#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+10; 
const int L = 30; 
// sum length
int trie[N * L][2], cnt = 1;
void insert(int x) {
    int crt = 0;
    for (int i = L-1; i >= 0; i--) {
        int& to = trie[crt][x>>i&1];
        if (to == 0) to = cnt++;
        crt = to;
    }
}
int get(int crt, int i) {
    if (i < 0) return 0;
    assert(trie[crt][0] || trie[crt][1]);
    if (!trie[crt][0]) return get(trie[crt][1], i-1);
    if (!trie[crt][1]) return get(trie[crt][0], i-1);
    return min(get(trie[crt][0], i-1), get(trie[crt][1], i-1))  +  (1<<i);
}

void solve() {
    int n; cin >> n;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        insert(x);
    }
    cout << get(0, L-1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
