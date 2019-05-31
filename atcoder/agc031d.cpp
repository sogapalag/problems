#include <bits/stdc++.h>

using namespace std;

vector<int> operator*(const vector<int>& a, const vector<int>& b) {
    int sz = a.size();
    vector<int> c(sz);
    for (int i = 0; i < sz; i++) {
        c[i] = a[b[i]];
    }
    return c;
}
vector<int> inv(const vector<int>& a) {
    int sz = a.size();
    vector<int> c(sz);
    for (int i = 0; i < sz; i++) {
        c[a[i]] = i;
    }
    return c;
}
vector<int> vpow(vector<int>& a, int exp) {
    int sz = a.size();
    vector<int> c(sz);
    iota(c.begin(), c.end(), 0);
    for (; exp; exp>>=1) {
        if (exp&1)
            c = c * a;
        a = a * a;
    }
    return c;
}

// non commutative, but associative.
// check out permutation wiki, group theory
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> p(n+1);
    vector<int> q(n+1);
    p[0] = q[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> q[i];
    }
    vector<int> ip = inv(p);
    vector<int> iq = inv(q);
    int exp = (k-1) / 6;
    int rem = (k-1) % 6;
    vector<int> base = q*ip*iq*p;
    vector<int> lhs = vpow(base, exp);
    vector<int> rhs = inv(lhs);
    vector<int> mid;
    if      (rem == 0) mid = p;
    else if (rem == 1) mid = q;
    else if (rem == 2) mid = q*ip;
    else if (rem == 3) mid = q*ip*iq;
    else if (rem == 4) mid = q*ip*iq*p*iq;
    else if (rem == 5) mid = q*ip*iq*p*p*iq;
    vector<int> res = lhs * mid * rhs;
    for (int i = 1; i <= n; i++) {
        cout << res[i] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
