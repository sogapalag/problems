#include <bits/stdc++.h>

using namespace std;

using ll=long long;
using Point=pair<int, int>;
void solve() {
    int h,w,n;
    cin >> h >> w >> n;
    set<Point> st;
    for (int _ = 0; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        st.insert({x,y});
    }
    set<Point> trk;
    vector<ll> cnt(10, 0);
    for (auto& p: st) {
        int x,y;
        tie(x,y) = p;
        for (int u = x-2; u <= x; u++) {
            for (int v = y-2; v <= y; v++) {
                if (u <= 0 || v <= 0) continue;
                if (u+2 > h || v+2 > w) continue;
                if (trk.find({u,v}) != trk.end()) continue;
                int sum = 0;
                for (int i = u; i < u+3; i++) {
                    for (int j = v; j < v+3; j++) {
                        if (st.find({i,j}) != st.end()) sum++;
                    }
                }
                cnt[sum]++;
                trk.insert({u,v});
            }
        }
    }
    ll sum = 0;
    for (int i = 1; i < 10; i++) {
        sum += cnt[i];
    }
    cnt[0] = 1ll*(h-2)*(w-2) - sum;
    for (auto& x: cnt) {
        cout << x << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
