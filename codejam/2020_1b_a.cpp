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
#define dbg(args...) 2020
#endif

void __solve() {
    int x,y;
    cin >> x >> y;
    char dx[2] = {'E', 'W'};
    char dy[2] = {'N', 'S'};
    if (x < 0) {
        x *= -1;
        swap(dx[0], dx[1]);
    }
    if (y < 0) {
        y *= -1;
        swap(dy[0], dy[1]);
    }
    if ((x^y)%2 == 0) { // no(0,0)case
        cout << "IMPOSSIBLE\n"; return;
    }
    auto high = [](int n){
        if (n==0) return 0;
        return 32 - __builtin_clz(n);
    };
    int n = max(high(x), high(y));
    int a=x,b=y, px=0,py=0;
    int z = x^y;
    for (int i = 0; i < n; i++) {
        if (z>>i&1) {
            if (z>>(i+1)&1) continue;
            // 0..01
            int j = i+1;
            while (j+1 <= n && !(z>>(j+1)&1)) {
                ++j;
            }
            // WA, consider (2,7)
            // 0010 , oxxo
            // 0111 , xoox
            if (x>>j&1) { // must 0,0
        cout << "IMPOSSIBLE\n"; return;
            }
            if (j==i+1 && j==n) continue; // no need
            int fx = (x>>i&1);
            if (fx) {
                for (int k = i+1; k <= j; k++) {
                    a ^= 1<<k;
                }
                for (int k = i; k < j; k++) {
                    px ^= 1<<k;
                }
            } else {
                for (int k = i+1; k <= j; k++) {
                    b ^= 1<<k;
                }
                for (int k = i; k < j; k++) {
                    py ^= 1<<k;
                }
            }
        }
    }

    int ckx = 0, cky = 0;
    string res;
    z=a^b;
//debug(z, a, b, px, py); return;
    for (int i = 0; i <= n; i++) {
        if (z>>i&1) {
            if (a>>i&1) {
                int p = px>>i&1;
                ckx += (p?-1:1)*(1<<i);
                res.push_back(dx[p]);
            } else {
                int p = py>>i&1;
                cky += (p?-1:1)*(1<<i);
                res.push_back(dy[p]);
            }
        }
    }
    assert(ckx == x && cky == y);
    cout << res << "\n";
}

void solve() {
    int x,y;
    cin >> x >> y;
    char dx[2] = {'E', 'W'};
    char dy[2] = {'N', 'S'};
    if (x < 0) {
        x *= -1;
        swap(dx[0], dx[1]);
    }
    if (y < 0) {
        y *= -1;
        swap(dy[0], dy[1]);
    }
    if ((x^y)%2 == 0) { // no(0,0)case
        cout << "IMPOSSIBLE\n"; return;
    }
// https://codeforces.com/blog/entry/76281?#comment-607447
    int n = 32-__builtin_clz(x+y);
    int z = (1ll<<n) - 1;
    int a = (z*1ll + x+y)/2; // N+E
    int b = z-a; // S+W
    int c = a-x; // N+W
    int N = a&c;
    int E = a-N;
    int W = c-N;
    int S = b-W;
    string res;
    for (int i = 0; i < n; i++) {
        int bN = N>>i&1;
        int bE = E>>i&1;
        int bW = W>>i&1;
        int bS = S>>i&1;
        assert(bN+bE+bW+bS == 1);
        if (bE) res.push_back(dx[0]);
        if (bW) res.push_back(dx[1]);
        if (bN) res.push_back(dy[0]);
        if (bS) res.push_back(dy[1]);
    }
    cout << res << "\n";
}

// another easy method
// https://codeforces.com/blog/entry/76281?#comment-607502
// key, next layyer (x+1)/2,y/2  or (x-1)/2,y/2. by parity only one branch valid. i.e. unique valid.
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
