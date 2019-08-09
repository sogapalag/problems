#include <bits/stdc++.h>

using namespace std;


// wlog, x,insert+1, means f(x) curve, x>=x* all +1.
// so wanna make bound-size smaller, mins,maxs value must all appear before another.
void solve() {
    string s;
    cin >> s;
    vector<int> h, v;
    h.push_back(0);
    v.push_back(0);
    int x = 0, y = 0;
    for (auto& c: s) {
        if (c == 'A') {
            x--; h.push_back(x);
        }
        if (c == 'D') {
            x++; h.push_back(x);
        }
        if (c == 'W') {
            y++; v.push_back(y);
        }
        if (c == 'S') {
            y--; v.push_back(y);
        }
    }
    auto dim = [&](auto& a)->pair<int,bool>{
        int mi = 1e8, mx = -1e8;
        for (auto& x: a) {
            mi = min(mi, x);
            mx = max(mx, x);
        }
        int len = mx - mi + 1;
        if (len <= 2) return {len, 0};
        int k = -1;
        int cnt = 0;
        for (auto& x: a) {
            if (x == mi) {
                if (k == 1)
                    cnt++;
                k = 0;
            }
            if (x == mx) {
                if (k == 0)
                    cnt++;
                k = 1;
            }
        }
        return {len, cnt < 2};
    };
    int X, Y; bool A, B;
    tie(X, A) = dim(h);
    tie(Y, B) = dim(v);
    long long res = 1ll*X*Y;
    if (A) res = min(res, 1ll*(X-1)*Y);
    if (B) res = min(res, 1ll*X*(Y-1));
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
