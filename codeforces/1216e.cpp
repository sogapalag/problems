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

using ll=long long ;
const int N = 100005; 
ll df[N], f[N], g[N]; // f[i] = [1..i], g[i] = [f[1]..f[i]]
const int M = 20; 
ll F[M]; // F[i] = f[10^i - 1].  i.e. to digit i's 9..99
ll dh[M], h[M]; // h[i] = g[10^i - 1]

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}


int calc(ll n) {
dbg(n);
    // find which BIG block
    int i = bs_first<int>(1, 10, [&](int i){
            return h[i] >= n;
            });
    n -= h[i-1];
dbg(i, n);
    assert(0 < n && n <= dh[i]);
    ll y = pow(10, i-1);
    ll x = 9*y;
dbg(x, y);
    auto sg = [&](ll j)->ll{
        if (j < 0) return 0;
        ll sum = (j+1) * F[i-1];
        sum += (j+1)*(j+2)/2 * i;
        return sum;
    };
    // find which line of BIG block
    ll j = bs_first<ll>(0, x, [&](ll j){
            return sg(j) >= n;
            });
    n -= sg(j-1);
dbg(j, n);
    assert(n > 0);
    j = y + j;
    // find which small block
    int k = bs_first<int>(1, 10, [&](int k){
            return F[k] >= n;
            });
    n -= F[k-1];
dbg(k, n);
    assert(n > 0);
    n--;
    // get nth after 10^{k-1}, di digit
    ll nth = n/k; int di = n%k;
    x = pow(10, k-1) + nth;
dbg(nth, di);
    int res = to_string(x)[di] - '0';
    return res;
}

void solve() {
    for (int i = 1; i < N; i++) {
        df[i] = to_string(i).size();
        f[i] = f[i-1] + df[i];
        g[i] = g[i-1] + f[i];
    }

    for (int i = 1; i < 10; i++) {
        ll y = pow(10, i-1);
        ll x = 9 * y;
        F[i] += F[i-1] + i * x;
        dh[i] = x * F[i-1] +  i*x*(x+1)/2;
        h[i] = h[i-1] + dh[i];
        if (i < 6) {
assert(F[i] == f[x+y-1]);
assert(h[i] == g[x+y-1]);
        }
        //cout << h[i] << "\n";
    }

    int q; cin >> q;
    while (q--) {
        ll n; cin >> n;
        cout << calc(n) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
