#include <bits/stdc++.h>

using namespace std;
using ll=long long;

enum Mono {
    None,
    Inc,
    Dec
};
Mono mono(const vector<ll>& a) {
    bool inc = false;
    bool dec = false;
    for (int i = 1; i < (int)a.size(); i++) {
        if (a[i-1] < a[i]) {
            if (dec) return None;
            inc = true;
        } else if (a[i-1] > a[i]) {
            if (inc) return None;
            dec = true;
        } else return None;
    }
    return inc ? Inc : Dec;
}
void roll_back(vector<ll>& a) {
    for (int i = a.size()-1; i >= 1; i--) {
        a[i] -= a[i-1];
    }
}
const int LIM = 2e5;

// note upper bound is binomial
// when n >= 3, #P is acceptable. brute-force
//  for n = 2, handle with euclid style
// also note key property for roll_back-able b should be monotonic.
void solve() {
    int n; cin >> n;
    vector<ll> a(n), b(n);
    for (auto& x: a) cin >> x;
    for (auto& x: b) cin >> x;
    if (n == 1) {
        if (a[0] == b[0]) {
            cout << "SMALL\n0\n\n";
        } else {
            cout << "IMPOSSIBLE\n";
        }
        return;
    }
    ll sa = accumulate(a.begin(), a.end(), 0ll);
    ll sb = accumulate(b.begin(), b.end(), 0ll);
    auto ra = a;
    reverse(ra.begin(), ra.end());

if (n == 2) {
    // normalize
    bool rev = false;
    if (a[0] > a[1]) {
        rev = true;
        swap(a[0], a[1]);
    }
    vector<ll> res;
    if (b[0] > b[1]) {
        res.push_back(0);
        swap(b[0], b[1]);
    }
    while (true) {
        sb = b[0] + b[1];
        if (sa > sb || a[0] > b[0]) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        if (sa == sb) {
            if (a == b) {
                if (rev) res.push_back(0);
                auto cnt = accumulate(res.begin(), res.end(), 0ll);
                if (cnt > LIM) {
                    cout << "BIG\n" << cnt << '\n';
                } else {
                    string s;
                    for (auto x: res) {
                        if (x > 0) {
                            while (x--) s.push_back('P');
                        } else s.push_back('R');
                    }
                    reverse(s.begin(), s.end());
                    cout << "SMALL\n";
                    cout << s.size() << '\n' << s << '\n';
                }
            } else {
                cout << "IMPOSSIBLE\n";
            }
            return;
        }
        if (a[0] == b[0]) {
            if (b[1] > a[1] && (b[1]-a[1])%a[0] == 0) {
                res.push_back((b[1]-a[1]) / b[0]); b[1] = a[1];
            } else {
                cout << "IMPOSSIBLE\n";
                return;
            }
        } else {
            auto b1 = b[1]%b[0];
            res.push_back((b[1]-b1) / b[0]); b[1] = b1;
            if (b[0] > b[1]) {
                swap(b[0], b[1]);
                res.push_back(0);
            }
        }
    }
    return;
}
    
    string res;
    int cnt = 0;
    while (true) {
        if (sa > sb) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        if (sa == sb) {
            if (ra == b) {
                res.push_back('R');
                reverse(b.begin(), b.end());
            }
            if (a == b) {
                reverse(res.begin(), res.end());
                if (cnt > LIM) {
                    cout << "BIG\n" << cnt << '\n';
                } else {
                    cout << "SMALL\n" << res.size() << '\n' << res << '\n';
                }
            } else {
                cout << "IMPOSSIBLE\n";
            }
            return;
        }
        auto type = mono(b);
        if (type == None) {
            cout << "IMPOSSIBLE\n";
            return;
        } else if (type == Inc) {
            res.push_back('P');
            roll_back(b); cnt++;
            sb = accumulate(b.begin(), b.end(), 0ll);
        } else {
            res.push_back('R');
            reverse(b.begin(), b.end());
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
