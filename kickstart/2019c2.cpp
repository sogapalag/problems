#include <bits/stdc++.h>

using namespace std;

const int N = 305; 

int v[N][N];
int d[N][N];
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> v[i][j];
        }
    }
    memset(d, -1, sizeof d);
    // or use two deques, one sort min/max. new value comin pop useless, push correspoding pos. O(n)
    for (int i = 1; i <= n; i++) {
        int y = 1;
        multiset<int> st;
        st.emplace(v[i][1]);
        for (int j = 1; j <= m; j++) {
            while (y <= m && *st.rbegin() - *st.begin() <= k) {
                y++;
                if (y <= m)
                    st.emplace(v[i][y]);
            }
            d[i][j] = y - j;
            auto it = st.find(v[i][j]);
            st.erase(it);
        }
    }
    int res = 0;
    // largest rectangle area histogram.
    for (int j = 1; j <= m; j++) {
        vector<int> stk; stk.reserve(n+2);
        stk.emplace_back(0);
        for (int i = 1; i <= n+1; i++) {
            while (d[i][j] < d[stk.back()][j]) {
                int ht = d[stk.back()][j]; stk.pop_back();
                int tmp = ht * (i - stk.back() - 1);
                res = max(res, tmp);
            }
            stk.emplace_back(i);
        }
    }
    cout << res;
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
