#include <bits/stdc++.h>

using namespace std;

#undef LOCAL
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

int n;
string s;

vector<int> d2;

// d1 odd, default 1
// d2 even, default 0, i as right
// radius
void manacher() {
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 0 : min(d2[l+r-i+1], r-i+1);
        while (0 <= i-k-1 && i+k < n && s[i-k-1] == s[i+k]) {
            k++;
        }
        d2[i] = k--;
        if (i+k > r) {
            l = i-k-1;
            r = i+k;
        }
    }
}


// s = t0 t_{n-1} t_1 t_{n-2}... aka BWBW.... black = t, white = t.rev();
// then valid iff is palidrome in s. with even-length, contain odd B.
// the radius in s is actually length in original t.
void solve() {

    cin >> n;
    string t; cin >> t;
    s.resize(2*n);
    for (int i = 0; i < n; i++) {
        s[2*i] = t[i];
        s[2*n-2*i-1] = t[i];
    }
    d2.resize(2*n);
    n*=2; manacher(); n/=2;

    int m = n/2;

    vector<int> mx(n, -1);

    for (int i = 0; i < m; i++) {// carefual < m, since s itself is paildrome.
        int j = 2*i+1;
        if (d2[j]%2==0) d2[j]--;
        if (d2[j]>0) {
            int k = (j - d2[j])/2;
            mx[k] = max(mx[k], d2[j]);
        }
    }
    dbg(mx);

    // res[i]: variant-prefix max, since valid iff the valid box[l,r] that l<=i
    for (int i = 1; i < m; i++) {
        mx[i] = max(mx[i], mx[i-1]-2); // whenever move right 1 step, before valid length -2
    }
    for (int i = 0; i < m; i++) {
        if (mx[i] <= 0) mx[i] = -1;
        cout << mx[i] << ' ';
    }
    if (n&1) cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
