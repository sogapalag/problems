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

// for cut by board=0, we can make one seg's 1 nodes -2 to become board
// for cut by board=1, we can make one seg's 2=(1+1) nodes -2 to merge with 0s
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<int> a(2*n+1);
    for (int i = 0; i < n; i++) {
        int x = s[i]=='('? 1 : -1;
        a[i+1] = a[i+1+n] = x;
    }
    for (int i = 1; i <= 2*n; i++) {
        a[i] += a[i-1];
    }
dbg(a);
    if (a[n] != 0) {
        cout << "0\n1 1"; return;
    }
    int Z = 0, k = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < Z) {
            Z = a[i];
            k = i;
        }
    }
dbg(Z,k);
    int base;
    auto calc = [&](int c)->tuple<int,int,int>{
        vector<int> cut;
        for (int i = k; i <= n+k; i++) {
            if (a[i] == Z+c) cut.emplace_back(i);
        }
        int mx = 0, l = 1, r = 1;
        int m = cut.size();
dbg(cut);
        if (c == 0) base = m;
        for (int i = 1; i < m; i++) {
            int cnt = 0;
            for (int j = cut[i-1]; j < cut[i]; j++) {
                if (a[j] == Z+c+1) cnt++;
            }
            if (cnt > mx) {
                mx = cnt;
                l = cut[i-1]+1;
                r = cut[i];
            }
        }
        return {mx,l,r};
    };
    int one, l1, r1;
    tie(one, l1, r1) = calc(0);
    int two, l2, r2;
    tie(two, l2, r2) = calc(1);
    auto f = [&](int& x){
        if (x > n) x-=n;
    };
    f(l1); f(l2); f(r1); f(r2);

    if (one > base+two-1) {
        cout << one << "\n";
        cout << l1 << ' ' << r1;
    } else {
        cout << base+two-1 << "\n";
        cout << l2 << ' ' << r2;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
