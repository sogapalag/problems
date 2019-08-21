#include <bits/stdc++.h>

using namespace std;


// 1,2,4,8..
// small diamond move UDLR make a bigger diamond
void solve() {
    int n; cin >> n;
    int odd=0, even=0;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        if ((x+y)&1) odd++;
        else even++;
        a[i] = {x,y};
    }
    if (odd && even) {
        cout << -1; return;
    }

    int m = 35;
    vector<int64_t> d(m);
    for (int i = 0; i < m; i++) {
        d[i] = 1ll << i;
    }
    reverse(d.begin(), d.end());
    cout << (even?m+1:m) <<"\n";
    for (auto& x: d) {
        cout << x << ' ';
    }
    cout << (even?"1\n":"\n");
    for (auto& p: a) {
        int64_t x,y;
        tie(x,y) = p;
        if (even) x--;
        string res;
        for (int i = 0; i < m; i++) {
            bool u = y+x>0 , v = y-x>0;
            if (u && v)   res += "U", y -= d[i];
            if (!u && !v) res += "D", y += d[i];
            if (u && !v)  res += "R", x -= d[i];
            if (!u && v)  res += "L", x += d[i];
        }
        assert(x == 0 && y == 0);
        if (even) res += "R";
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
