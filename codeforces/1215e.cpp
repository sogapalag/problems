#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Fenwick {
    int n;
    vector<T> v;
    
    Fenwick(int size = 100005) : n(size), v(n+1, 0) {}
    inline void add(int p, T val) {
        for (; p <= n; p += (p&-p)) { v[p] += val; }
    }
    inline T query(int p) {
        T tmp = 0;
        for (; p > 0; p -= (p&-p)) { tmp += v[p]; }
        return tmp;
    }
    inline T query(int l, int r) {
        return query(r) - query(l-1);
    }
};

// sum of cross inversions
// TODO rigorous proof?
void solve() {
    int n; cin >> n;
    vector<int> a[20];
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        a[x-1].emplace_back(i);
    }
    long long res = 0;
    for (int k = 0; k < 20; k++) {
        Fenwick<int> st(n);
        for (int p: a[k]) st.add(p, 1);
        for (int i = k+1; i < 20; i++) {
            long long sum = 0;
            for (int p: a[i]) sum += st.query(p);
            long long tot = 1ll*a[k].size() * a[i].size();
            sum = min(sum, tot-sum);
            res += sum;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
