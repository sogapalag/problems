#include <bits/stdc++.h>

using namespace std;
using ll=long long;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Segment {
    ll l, r;
    Segment() {}
    Segment(ll _l, ll _r) : l(_l), r(_r) {}
    ll len()const {
        return r-l;
    }
    bool operator<(const Segment& _oth) const {
        return r-l > _oth.r - _oth.l;
    }
};
#define LOCAL
string to_string(Segment s) { return "(" + to_string(s.l) + "," + to_string(s.r) + ")"; }
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
const ll B = 1e10;
const ll N = 1e12;
vector<Segment> a;
int win = 0;

//#define SIMULATE

void upd(ll x){
    auto it = a.begin();
    while (it != a.end()) {
        if (it->l <= x && x + B <= it->r) break;
        ++it;
    }
    assert(it != a.end());
    Segment left = {it->l, x};
    Segment right = {x+B, it->r};
    a.erase(it);
    if (left.len() >= B) a.push_back(left);
    if (right.len()>= B) a.push_back(right);
    sort(a.begin(), a.end());
}
ll ai(){
#ifdef SIMULATE
    // not random range.
    if (a.empty()) return -2;
    int i = rng()%a.size();
    ll x = rng()%(a[i].len() - B + 1);
    x += a[i].l;
dbg("ai", x, a);
    upd(x);
    if (a.empty()) return -3;
    return x;
#else
    ll x; cin >> x;
    if(x>0)upd(x);
    return x;
#endif
}
void me(ll x){
#ifdef SIMULATE
dbg("me", x, a);
#else
    cout << x << endl;
#endif
    upd(x);
}
// B)  3B-1) 3B)    5B-1) 5B) ...
// L    W   L     W      L
void solve() {
    a.clear();
    a.emplace_back(1, N);
    while (true) {
        ll x = ai();
        if (x < 0) {
            assert(x!=-1);
            if (x==-2)win++;
            break;
        }
        // 100%
        if (a[0].len() >= 3*B) {
            me(a[0].l+2*B);
        } else if (a[0].len() > 2*B){
            ll x = a[0].l + (a[0].len() - B)/2;
            me(x);
        } else {
            // remain some 2B .. and <2B
            // they all look like B to ai. since random
            // so when we face last 2B, we can dicide by parity
            if (a.size()&1){
                me(min(a[0].l+1, a[0].r-B));
            } else {
                me(a[0].l);
            }
        }
        //{// 50%
        //    ll x = a[0].l + (a[0].len() - B)/2;
        //    me(x);
        //}
        //// 77%
        //if (a.size() >= 2 || a[0].len() > 5*B) {
        //    ll x = a.back().l;
        //    me(x);
        //} else {
        //    if (a[0].len() < 3*B) {
        //        ll x = min(a[0].l + B-1, a[0].r - B);
        //        me(x);
        //    } else {
        //        ll d = a[0].len() - B;
        //        d /= 2;
        //        ll x = min(a[0].l + d, a[0].r - B);
        //        me(x);
        //    }
        //}
    }
}

// keep in mind what format needed!! might WA!
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int _w;
    int T; cin >> T >> _w;
    for (int t = 1; t <= T; t++) {
        solve();
        //int verdict; cin >> verdict;
        //assert(verdict == 1);
    }
#ifdef SIMULATE
    cout << win << '\n';
    cout << double(win)/T;
#else
#endif
    return 0;
}
