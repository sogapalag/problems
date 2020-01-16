#include <bits/stdc++.h>

using namespace std;

int n,m;
using pi=pair<int, int>;
pair<int, pi> get_best(vector<vector<int>>& a) {
    const int MSK = 1<<m; 
    vector<pi> mx(MSK); // previous max of mi_msk
    int best = 0;
    pi p = {0,0}; // could same
    for (int i = 0; i < n; i++) {
        vector<int> id(m);
        iota(id.begin(), id.end(), 0);
        sort(id.begin(), id.end(), [&](auto& u, auto& v){
            return a[i][u] < a[i][v];
        });
        int msk = 0;
        for (int j: id) {
            if (msk == 0) {
                if (a[i][j] > best) {
                    best = a[i][j];
                    p = {0, i};
                }
            } else {
                int x, k;
                tie(x, k) = mx[msk];
                if (x >= a[i][j] && a[i][j] > best) {
                    best = a[i][j];
                    p = {k, i};
                }
            }
            msk |= 1<<j;
        }
        for (int msk = 1; msk < MSK; msk++) {
            int mi = 1e9;
            for (int j = 0; j < m; j++) {
                if (msk>>j&1) mi = min(mi, a[i][j]);
            }
            if (mi > mx[msk].first) {
                mx[msk] = {mi, i};
            }
        }
    }
    return {best, p};
}

void __solve() {
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    auto res = get_best(a);
    reverse(a.begin(), a.end());
    auto ans = get_best(a);
    if (res.first >= ans.first) {
        int i,j;
        tie(i,j) = res.second;
        cout << i+1 << ' ' << j+1;
    } else {
        int i,j;
        tie(i,j) = ans.second;
        i=n-i; j=n-j;
        cout << i << ' ' << j;
    }
}

// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}
void solve() {
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    const int MSK = 1<<m; 
    int Ri, Rj;
    auto ck = [&](int val){
        vector<int> candi(MSK, -1);
        for (int i = 0; i < n; i++) {
            int msk = 0;
            for (int j = 0; j < m; j++) {
                if (a[i][j] >= val) {
                    msk |= 1<<j;
                }
            }
            candi[msk] = i;
        }
        for (int j = 0; j < m; j++) {
            for (int msk = 0; msk < MSK; msk++) {
                if (msk>>j&1) {
                    if (candi[msk] != -1) {
                        candi[msk^1<<j] = candi[msk];
                    }
                }
            }
        }
        for (int msk = 0; msk < MSK; msk++) {
            if (candi[msk] != -1 && candi[msk^(MSK-1)] != -1) {
                Ri = candi[msk];
                Rj = candi[msk^(MSK-1)];
                return true;
            }
        }
        return false;
    };
    int best = bs_last<int>(0, 1e9+10, ck);
    ck(best);
    cout << Ri+1 << ' ' << Rj+1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
