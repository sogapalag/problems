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
#define dbg(args...) 2020
#endif

// lower bound, #adj-rank-differ start(n*m-1) -> end(n-1). note each op dec at most 2.
// => LB = ceil((n*m-n)/2)
// then a naive method pick some seg [l..r) from bottom, s.t.a[r]=a[l-1], a[0]=a[r-1].
//  fortunately work. careful last op can be  22[0011]22
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(n*m), T(n*m);
    for (int i = 0; i < n*m; i++) {
        a[i] = i%n;
        T[i] = i/m;
    }
    int LB = (n*m - n + 1)/2;
    int res = 0;
    auto f = [&](int l, int r){
        vector<int> b;
        for (int i = l; i < r; i++) {
            b.push_back(a[i]);
        }
        for (int i = 0; i < l; i++) {
            b.push_back(a[i]);
        }
        for (int i = r; i < n*m; i++) {
            b.push_back(a[i]);
        }
        swap(a,b);
        if (a==b) return true;
        else {
            cout << l << ' ' << (r-l) << '\n';
            return false;
        }
    };
    cout << LB << "\n";
    while (a!=T) {
        int x = a[0];
        int i = n*m-2;
        while (!(a[i]==x && a[i+1]!=x)) {
            --i;
        }
        int y = a[i+1], j = i-1;
        while (a[j]!=y) {
            --j;
        }
        if (f(j+1,i+1)) {
            assert((n*m-n)&1);
            assert(a[0] == n-1);
            int l = 0;
            while (a[l]==n-1) {
                ++l;
            }
            int r = n*m-1;
            while (a[r]==n-1) {
                --r;
            }
            assert(!f(l,r+1));
            assert(a==T);
        }
dbg(a);
        res++;
    }
    //cerr<<LB<<endl;
    //cerr<<res<<endl;
    assert(res == LB);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
