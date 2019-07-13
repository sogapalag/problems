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

int win() {
    int n, k;
    cin >> n >> k;
    Fenwick<int> a(n);
    string s; cin >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            a.add(i+1, 1);
        }
    }
    for (int i = 1; i+k-1 <= n; i++) {
        int l = a.query(i-1);
        int r = a.query(i+k, n);
        if (l == i-1 && r == n - (i+k-1)) return 1;
        if (l == 0 && r == 0) return 1;
    }
    if (k < (n+1)/2) return 0;
    for (int i = 1; i+k-1 <= n; i++) {
        int l = a.query(i-1);
        int r = a.query(i+k, n);
        if ((l==0 || r==0) && (l==i-1 || r ==n-(i+k-1))) {
            continue;
        } else {
            return 0;
        }
    }
    return -1;
}
// no need BIT.. pre sum table enough
// conjecture, first step win or lose, future tie.
// then: win \E left&right all 1/0; lose, \A  \E left/right all 1.0
// and if A not win, k < half, tied.
// need rigorous proof TODO
void solve() {
    int res = win();
    if (res == 1) {
        cout << "tokitsukaze";
    } else if (res == 0) {
        cout << "once again";
    } else {
        cout << "quailty";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
