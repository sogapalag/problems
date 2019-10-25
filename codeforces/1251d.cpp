#include <bits/stdc++.h>

using namespace std;

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
#define dbg(args...) 2019
#endif

struct Node {
    int l, r;
    Node() {}
    Node(int _l, int _r) : l(_l), r(_r) {}
    bool operator<(const Node& _oth) const {
        return r > _oth.r;
    }
};
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
void solve() {
    int n; cin >> n;
    ll S; cin >> S;
    vector<Node> a(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        a[i] = {x, y};
    }
    sort(a.begin(), a.end());
    int res = bs_last<int>(1, 1e9+10, [&](int t){
            int i = bs_last<int>(0, n, [&](int i){
                    return a[i].r >= t;
                    });// don't use i, easy mix j
dbg(t, i);
            if (i < n/2) return false;
            i++;
            vector<int> candi(i);
            for (int j = 0; j < i; j++) {
                candi[j] = a[j].l;
            }
            sort(candi.begin(), candi.end(), greater<int>());
dbg(candi);
            ll sum = 0;
            for (int j = 0; j <= n/2; j++) {
                sum += max(candi[j], t);
            }
            for (int j = n/2 +1; j < i; j++) {
                sum += candi[j];
            }
            for (int j = i; j < n; j++) {
                sum += a[j].l;
            }
dbg(sum);
            return sum <= S;
            });
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
