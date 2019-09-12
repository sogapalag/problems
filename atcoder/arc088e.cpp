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

// optim: (l1,r1) out of (l2,r2) if l1<l2.
void solve() {
    string s; cin >> s;
    int n = s.size();
    vector<vector<int>> pos(26);
    for (int i = 0; i < n; i++) {
        pos[s[i]-'a'].emplace_back(i);
    }
    vector<int> l(26, 0), r(26);
    vector<int> odd;
    for (int i = 0; i < 26; i++) {
        r[i] = pos[i].size();
        if (r[i]&1) odd.emplace_back(i);;
    }
    if (odd.size() > (n&1)) {
        cout << -1; return;
    }

    vector<bool> trk(n, false);
    vector<int> a(n);
    if (n&1) {
        int i = odd[0];
        int p = pos[i][r[i]/2];
        trk[p] = true;
        a[p] = n/2;
    }
    int L = 0, R = n;
    for (int i = 0; i < n; i++) {
        if (trk[i]) continue;
        int k = s[i]-'a';
        a[i] = L++;
        --r[k];
        a[pos[k][r[k]]] = --R;
        trk[i] = trk[pos[k][r[k]]] = true;
    }
    //for (int i = 0; i < n; i++) {
    //    cout << a[i] << '\n';
    //}
    reverse(a.begin(), a.end());
    long long res = 0;
    Fenwick<int> st(n);
    for (int x: a){
        x++;
        res += st.query(x);
        st.add(x, 1);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
