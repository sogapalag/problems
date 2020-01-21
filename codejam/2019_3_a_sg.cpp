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
vector<int> sg;
int win = 0;

#define SIMULATE

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
int SG() {
    int res = 0;
    for (auto& s: a) {
        res ^= sg[s.len()/B];
    }
    return res;
}
// B)  3B-1) 3B)    5B-1) 5B) ...
// L    W   L     W      L
// by try handwrite, can find above win/lose situation, notice L position are <<B, [3B-1],[5B-1], except ..B)
//   which implies we can ignore that, just treat the game as split i to (x,i-1-x) or (x,i-2-x)
//   i.e. only sg[0]=0, else sg[.]>0, since other losing position is little, and AI'random of course won't notice that.
//  thus we will have high prob sg>0, then always pick a winning move.
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
        int sum = SG();
        ll mv = -1;
        if (sum != 0) {
            for (auto& s: a) {
                int i = s.len()/B;
                for (int x = 0; x < i; x++) {
                    if ((sum ^ sg[i] ^ sg[x] ^ sg[i-1-x]) == 0) {
                        mv = s.l + x*B; break;
                    }
                }
                if (mv != -1)break;
                for (int x = 0; x < i-1; x++) {
                    if ((sum ^ sg[i] ^ sg[x] ^ sg[i-2-x]) == 0) {
                        // 100%
                        mv = s.l + x*B + (s.len()%B + B)/2;
                        // 99%
                        //mv = min(s.l + (x+1)*B - 1, s.r-B);
                        break;
                    }
                }
                if (mv != -1)break;
            }
        }
        if (mv == -1) {
            mv = a[0].l;
        }
        me(mv);
    }
}
void prep() {
    sg.assign(101, 0);
    for (int i = 1; i <= 100; i++) {
        set<int> s;
        for (int x = 0; x < i; x++) {
            s.insert(sg[x] ^ sg[i-1-x]);
        }
        for (int x = 0; x < i-1; x++) {
            s.insert(sg[x] ^ sg[i-2-x]);
        }
        // mex
        while (s.count(sg[i])) {
            ++sg[i];
        }
    }
}

// keep in mind what format needed!! might WA!
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    prep();
    int _w;
    int T; cin >> T >> _w;
    for (int t = 1; t <= T; t++) {
        solve();
        //int verdict; cin >> verdict;
        //assert(verdict == 1);
    }
#ifdef SIMULATE
    dbg(sg);
    cout << win << '\n';
    cout << double(win)/T;
#else
#endif
    return 0;
}
