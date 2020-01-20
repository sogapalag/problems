#include <bits/stdc++.h>

using namespace std;

struct Frac {
    int x, y;
    Frac() {}
    Frac(int _x, int _y) : x(_x), y(_y) {}
    bool operator<(const Frac& _oth) const {
        return x*1ll*_oth.y < _oth.x *1ll* y;
    }
    bool operator==(const Frac& _oth) const {
        return x*1ll*_oth.y == _oth.x*1ll*y;
    }
};

// for each incomparable pair. R=|dx/dy| split k=wy/wx, (0, +oo), decide a<b or a>b
//   res = #{distinct R} + 1
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        a[i]={x,y};
    }
    vector<Frac> fr;
    for (int i = 0; i < n; i++) {
        int x,y;
        tie(x,y)=a[i];
        for (int j = 0; j < i; j++) {
            int u,v;
            tie(u,v)=a[j];
            int dx = x-u;
            int dy = y-v;
            if (dx*1ll*dy < 0) {
                fr.emplace_back(abs(dx),abs(dy));
            }
        }
    }
    // or pre-insert p,q/gcd
    sort(fr.begin(), fr.end());
    fr.erase(unique(fr.begin(), fr.end()), fr.end());
    cout << fr.size()+1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
