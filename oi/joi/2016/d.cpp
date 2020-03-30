#include <bits/stdc++.h>

using namespace std;
using ll=long long;
using pl = pair<ll,ll>;

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

// wlog let A>0,B>=0.
// key: (x+kA,y+kB) -> (normalize) (x'+..A, y'+..B) s.t. 0<=x'<A
// now (x,y,..) occur with segments ..
// then for each-4, res += #intersect-points
void solve() {
    int n,k;
    cin >> n >> k;
    string s; cin >> s;
    ll A = 0, B = 0;
    vector<pl> a; a.reserve(n);
    for (char c:s) {
        if (c=='N')B++;
        if (c=='S')B--;
        if (c=='E')A++;
        if (c=='W')A--;
        a.emplace_back(A, B);
    }
#define x first
#define y second
    if (A == 0 && B == 0) {
        a.emplace_back(0, 0);
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
        int res = 0;
        for (auto& p: a) {
            auto q = p;
            ++q.x;
            if (*lower_bound(a.begin(), a.end(), q) != q) continue;
            ++q.y;
            if (*lower_bound(a.begin(), a.end(), q) != q) continue;
            --q.x;
            if (*lower_bound(a.begin(), a.end(), q) != q) continue;
            res++;
        }
        cout << res << "\n";
        return;
    }
    if (A == 0) {
        swap(A, B);
        for (auto& p: a) {
            swap(p.x, p.y);
        }
    }
    if (A < 0) {
        A *= -1;
        for (auto& p:a) p.x *= -1;
    }
    if (B < 0) {
        B *= -1;
        for (auto& p:a) p.y *= -1;
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
dbg(A,B,a);
    map<pl,vector<pl>> seg;
    {   // x+kA -> x'+k'A, x'<A
        seg[{0,0}].emplace_back(0, +1);
        seg[{0,0}].emplace_back(1, -1);
        for (auto& p: a) {
            auto x = (p.x%A+A)%A; // -
            auto i = (p.x-x)/A;
            p.x -= i*A;
            p.y -= i*B;
            seg[p].emplace_back(i, +1);
            seg[p].emplace_back(i+k, -1);
        }
    }
    {
        for (auto& _: seg) {
            // shrink
            auto& a = _.second;
            sort(a.begin(), a.end());
            vector<pl> b;
            int cnt = 0;
            for (auto& e: a) {
                if (cnt == 0) b.emplace_back(e.x, +1);
                cnt += e.y;
                if (cnt == 0) b.emplace_back(e.x, -1);
            }
            swap(a,b);
        }
    }
if(0){
    for (auto& p: seg) {
        dbg(p.x, p.y);
    }
}
    ll res = 0;
    for (auto& _: seg) {
        auto p = _.first;
        auto& a00 = _.second;
        ++p.y;
        if (seg.find(p) == seg.end()) continue;
        auto& a01 = seg[p];
        ++p.x;
        int c = 0;
        if (p.x == A) p.x = 0, p.y -= B, c=1; // y also
        if (seg.find(p) == seg.end()) continue;
        auto& a11 = seg[p];
        --p.y;
        if (seg.find(p) == seg.end()) continue;
        auto& a10 = seg[p];
        
        vector<pl> a;
        for (auto& p:a00)a.push_back(p);
        for (auto& p:a01)a.push_back(p);
        for (auto& p:a11)a.push_back({p.x-c, p.y});
        for (auto& p:a10)a.push_back({p.x-c, p.y});
        sort(a.begin(), a.end());
dbg(p, res, a);
        int cnt = 0;
        ll l;
        for (auto& p: a) {
            if (cnt == 4) res += p.x - l;
            cnt += p.y;
            if (cnt == 4) l = p.x;
        }
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
