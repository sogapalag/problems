#include <bits/stdc++.h>

using namespace std;

using ll=long long ;

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}

const int N = 256; 
ll g[N][N];

// bi-p. max matching
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, int>> player(n);
    vector<pair<int, int>> bike(m);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        player[i] = {x, y};
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        bike[i] = {x, y};
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ll dx = (player[i].first - bike[j].first);
            ll dy = (player[i].second - bike[j].second);
            g[i][j] = dx*dx + dy*dy;
        }
    }
    ll lim;
    vector<bool> trk(n, false);
    vector<int> left(m, -1);
    function<bool(int)> dfs = [&](int i){
        if (trk[i]) return false;
        trk[i] = true;
        for (int j = 0; j < m; j++) {
            if (g[i][j] > lim) continue;
            if (left[j] == -1 || dfs(left[j])) {
                left[j] = i;
                return true;
            }
        }
        return false;
    };
    ll res = bs_first<ll>(0, 1ll<<50, [&](ll x){
            lim = x;
            int cnt = 0;
            fill(left.begin(), left.end(), -1);
            for (int i = 0; i < n; i++) {
                fill(trk.begin(), trk.end(), false);
                if (dfs(i)) {
                    cnt++;
                }
            }
            return cnt >= k;
            });
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
