#include <bits/stdc++.h>

using namespace std;


// note, A,B are int. i.e. period is int.
// key is optim has some period 2^lg. by parity and divide. omit,check editorial proof.
void solve() {
    int n, _y1;
    cin >> n >> _y1;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int m, _y2;
    cin >> m >> _y2;
    vector<int> b(m);
    for (auto& x: b) {
        cin >> x;
    }

    int res = 0;
    {// could vertical
        map<int, int> cnt;
        for (int x: a) cnt[x]++;
        for (int x: b) cnt[x]++;
        for (auto& _: cnt) {
            res = max(res, _.second);
        }
    }
    for (int i = 0; i <= 30; i++) {
        int p = 1<<i; // period
        int mod = p<<1;
        map<int,int> cnt;
        for (int x: a) cnt[x%mod]++;
        for (int x: b) cnt[(x+p)%mod]++;
        for (auto& _: cnt) {
            res = max(res, _.second);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
