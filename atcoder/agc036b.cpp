#include <bits/stdc++.h>

using namespace std;

#define LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(bool x) { return (x ? "T" : "F"); }
string to_string(const char* s) { return to_string((string)s); }
template <typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename V>
string to_string(V v) {
    bool f = true; string res = "[";
    for (const auto& x: v) {
        if (!f) res += ", ";
        f = false;
        res += to_string(x); } res += "]";
    return res;
}
void debug() { cerr << endl; }
template <typename H, typename... T>
void debug(H h, T... t) { cerr << " " << to_string(h); debug(t...); }
#ifdef LOCAL
#define dbg(args...) cerr<<"("<<#args<<") =", debug(args)
#else
#define dbg(args...) 2019
#endif

using ll=long long ;
// to[j][i]: jump 2^j times, = new_i - i + 1
void solve() {
    int n; ll k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<int> las(200'005, -1);
    vector<vector<ll>> to(64, vector<ll>(n));
    for (int i = 0; i < 2*n; i++) {
        int x = a[i%n];
        if (las[x] != -1) {
            to[0][las[x]%n] = i - las[x] + 1;
        }
        las[x] = i;
    }
    dbg(to);
    ll lim = n*k;
    int J = 0;
    for (int j = 1; j < 64; j++) {
        for (int i = 0; i < n; i++) {
            ll d = to[j-1][i];
            to[j][i] = d + to[j-1][(i+d)%n];
        }
        if (to[j][0] > lim) {
            J = j; break;
        }
    }
    dbg(to);
    ll I = 0;
    while (true) {
        while (J>=0 && I + to[J][I%n] > lim) {
            J--;
        }
        dbg(I, J);
        if (J < 0) break;
        I += to[J][I%n];
        dbg(I, J);
    }
    assert(lim - I <= n);
    // las as flag, simulate process
    fill(las.begin(), las.end(), -1);
    vector<int> res;
    for (ll i = I; i < lim; i++) {
        int x = a[i%n];
        if (las[x] == -1) {
            res.push_back(x);
            las[x] = 1;
        } else {
            while (!res.empty() && las[x] != -1) {
                las[res.back()] = -1;
                res.pop_back();
            }
        }
    }
    for (auto& x: res) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
