#include <bits/stdc++.h>

using namespace std;

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
// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}
using ll=long long;
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
// note "whole"
void solve() {
    int n; cin >> n;
    vector<int> a(n), cnt(n+1);
    for (auto& x: a) {
        cin >> x;
        cnt[x] ^= 1;
    }
    int sum = 0;
    for (int x: cnt) sum += x;
    if (sum > 1) {
        cout << 0; return;
    }
    int l = 0, r = n-1;
    while (l < r && a[l] == a[r]) {
        l++; r--;
    }
    if (l >= r) {
        cout << (n*1ll*(n+1)/2); return;
    }
    // seg must include at least one of l,r
    // when use l, at least R?
    //  iff has >= other-side, and if len<half, remain-part is valid-palin
    auto ck = [&](int x){
        vector<int> freq(n+1);
        for (int i = l; i <= x; i++) {
            freq[a[i]]++;
        }
        int exl = r - (x-l);
        for (int i = r; i > x && i >= exl; i--) {
            freq[a[i]]--;
        }
        for (int z: freq) if (z < 0) return false;
        x++; exl--; // campare next
        while (x < exl && a[x] == a[exl]) {
            x++; exl--;
        }
        return x >= exl;
    };
    int R = bs_first<int>(l+1, r+1, ck);

    // when use r, at least L?
    auto ck2 = [&](int x){
        vector<int> freq(n+1);
        for (int i = x; i <= r; i++) {
            freq[a[i]]++;
        }
        int exr = l + (r-x);
        for (int i = l; i <= exr && i < x; i++) {
            freq[a[i]]--;
        }
        for (int z: freq) if (z < 0) return false;
        exr++; x--; // next
        while (exr < x && a[x] == a[exr]) {
            exr++; x--;
        }
        return exr >= x;
    };
    int L = bs_last<int>(l, r, ck2);
dbg(l,r,L,R);
    ll res = 0;
    if (R < r) res += (l+1) * 1ll * (r-R);
    if (l < L) res += (l+1) * 1ll * (L-l);
    res += (l+1)*1ll*(l+1);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
