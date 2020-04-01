#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+10; 
int c[N], cnt[N], freq[N];
int mx;
void add(int x) {
    --freq[cnt[x]];
    ++cnt[x];
    ++freq[cnt[x]];
    if (mx < cnt[x]) mx = cnt[x];
}
void del(int x) {
    --freq[cnt[x]];
    --cnt[x];
    ++freq[cnt[x]];
    if (!freq[mx]) --mx;
}

// first note it's optim to color in the beginning
// key: consider unfold from 01, each generated middle is even.
// so thm: valid form is [0*,1*] [00,11]* [0*,1*] . i.e. middle run are even length
// then for fix color, two way to match pair(i.e. run-left-pos is odd/even pos)
//   i <-> (i-k)^1 + k, i.e. 23 or 12
// always change its pair to color x. since won't be worse then change it
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> pos(m+1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        add(c[i]);
        pos[c[i]].push_back(i);
    }
    for (int x = 1; x <= m; x++) {
        c[0] = c[n+1] = x;
        int res = n - cnt[x];
        for (int _:pos[x]) del(x);
        int extra = 0; // remain mx, can be reserved unchange
        for (int k:{0,1}) {
            for (int i:pos[x]) {
                i = ((i-k)^1)+k;
                if (c[i] != x) del(c[i]);
            }
            extra = max(extra, mx);
            for (int i:pos[x]) {
                i = ((i-k)^1)+k;
                if (c[i] != x) add(c[i]);
            }
        }
        res -= extra;
        cout << res << "\n";
        for (int _:pos[x]) add(x);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
