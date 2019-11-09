#include <bits/stdc++.h>

using namespace std;

// make sure permutation is [0..=n-1]
struct Perm : vector<int> {
    using vector<int>::vector;
    Perm() {}
    Perm(initializer_list<int> list) : vector<int>(list) {}

};

Perm& operator*=(Perm& a, const Perm& b) {
    assert(a.size() == b.size());
    int n = a.size();
    Perm _a(a);
    for (int i = 0; i < n; i++) {
        a[i] = _a[b[i]];
    }
    return a;
}
Perm operator*(const Perm& a, const Perm& b) {
    assert(a.size() == b.size());
    int n = a.size();
    Perm c(n);
    for (int i = 0; i < n; i++) {
        c[i] = a[b[i]];
    }
    return c;
}
Perm pinv(const Perm& a) {
    int n = a.size();
    Perm c(n);
    for (int i = 0; i < n; i++) {
        c[a[i]] = i;
    }
    return c;
}
Perm& operator/=(Perm& a, const Perm& b) {
    return a *= pinv(b);
}
Perm operator/(const Perm& a, const Perm& b) {
    return a * pinv(b);
}
Perm ppow(Perm a, int64_t e) {
    if (e < 0) {
        a = pinv(a);
        e *= -1;
    }
    int n = a.size();
    Perm c(n);
    iota(c.begin(), c.end(), 0);
    for (; e; e>>=1) {
        if (e&1) c *= a;
        a *= a;
    }
    return c;
}
int cycles_cnt(Perm a) {
    int cnt = 0, n = a.size();
    for (int i = 0; i < n; i++) {
        if (~a[i]) {
            cnt++;
            for (int j = i; ~a[j];) {
                int nxt = a[j];
                a[j] = -1;
                j = nxt;
            }
        }
    }
    return cnt;
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    vector<pair<int, int>> s(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        int y; cin >> y;
        s[i] = {a[i], y};
    }
    sort(a.begin(), a.end());
    sort(s.begin(), s.end(), [&](auto& u, auto& v){
        return u.second < v.second;
    });
    for (int i = 0; i < n; i++) {
        if (a[i] > s[i].second) {
            cout << "No"; return;
        }
    }
    // not unique perm, p'=p* swap, so always find no one-cycle
    for (int i = 1; i < n; i++) {
        if (a[i] <= s[i-1].second) {
            cout << "Yes"; return;
        }
    }

    Perm p(n);
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](auto& u, auto& v){
        return s[u].first < s[v].first;
    });
    int c = cycles_cnt(p);
    cout << (c>1?"Yes":"No");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
