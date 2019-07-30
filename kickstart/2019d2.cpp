#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

// for consulate, can at most by one clock pos across, by one anti-clock pos across.
// i.e. find latest pos across which, made these pos' res +1.
void solve() {
    int n, g, m;
    cin >> n >> g >> m;
    vector<int> H(g);
    vector<bool> D(g);
    for (int i = 0; i < g; i++) {
        int h; char c;
        cin >> h >> c;
        H[i] = h-1;
        D[i] = c=='C';
    }
    vector<int> a, c;
    for (int i = 0; i < g; i++) {
        if (D[i]) {
            c.emplace_back(H[i]-n);
            c.emplace_back(H[i]);
            c.emplace_back(H[i]+n);
        } else {
            a.emplace_back(H[i]-n);
            a.emplace_back(H[i]);
            a.emplace_back(H[i]+n);
        }
    }
    sort(a.begin(), a.end());
    sort(c.begin(), c.end());
    vector<int> res_c(n, 0), res_a(n, 0);
    for (int i = 0; i < n; i++) {
        int ic = ((i-m)%n + n) % n; // time-rev pos
        int ia = (i+m)%n;
        int clst_c = lower_bound(c.begin(), c.end(), ic) - c.begin(); // latest across which
        int dis_c = c.empty()?INF: c[clst_c] - ic;  // their dist.
        int clst_a = upper_bound(a.begin(), a.end(), ia) - a.begin() - 1;
        int dis_a = a.empty()?INF: ia - a[clst_a];
        if (dis_c > m && dis_a > m) continue;
        if (dis_c <= dis_a)
            res_c[(c[clst_c]+n)%n]++;
        if (dis_a <= dis_c)
            res_a[(a[clst_a]+n)%n]++;
    }
    for (int i = 0; i < g; i++) {
        if (D[i]) {
            cout << res_c[H[i]] << ' ';
        } else {
            cout << res_a[H[i]] << ' ';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
