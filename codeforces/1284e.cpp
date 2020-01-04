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
using pnt = complex<double>;
using ll=long long;

double PI = acos(-1);

ll c2(ll n){return n*(n-1)/2;}
ll c3(ll n){return n*(n-1)*(n-2)/6;}
ll c5(ll n){return n*(n-1)*(n-2)*(n-3)*(n-4)/120;}

struct Point {
    ll x, y;
    Point() {}
    Point(ll _x, ll _y) : x(_x), y(_y){}
};
Point operator-(const Point& u, const Point& v) {
    return {u.x - v.x, u.y - v.y};
}
ll cross(const Point& u, const Point& v) {
    return u.x * v.y - u.y * v.x;
}

void __solve() {
    int n; cin >> n;
    vector<pnt> a(n);
    for (int i = 0; i < n; i++) {
        double x,y;
        cin >> x >> y;
        a[i]={x,y};
    }
    long long res = 0;
    for (int i = 0; i < n; i++) {
        vector<double> deg;
        for (int j = 0; j < n; j++) {
            if (i!=j) {
                double x = arg((a[j]-a[i]));
                deg.push_back(x);
                deg.push_back(x+2*PI);
            }
        }
        sort(deg.begin(), deg.end());
dbg(deg);
        int m = n-1;
        ll tmp = c3(m);
        for (int j = 0; j < m; j++) {
            int k = lower_bound(deg.begin(), deg.end(), deg[j] + PI) - deg.begin();
            tmp -= c2(k-j-1);
        }
        res += tmp;
    }
    res *= (n-4);
    res /= 2;
    cout << res;
}

// polygon not have to be convex.
// there're 3 cases, convex-3,4,5.   3,4 are both valid.
// note a valid (p,4). there're exactly 2 triangle-contain-p.
// so we can find K = #(p, tri), then res = K*(n-4)/2
//   for calc K, calc its complement, iff consider all vs p-x, fix some x, select 2 from one-side.
// editorial: ans = 2x_3 + x_4. where x_i means #convex-i of 5 points.
//   and note x_3+x_4+x_5 = (n 5)
//   calc 3x_3 + 4x_4 + 5x_5 = #edge in convex
//  so for fix edge, select 3 points from one-side
void solve() {
    int n; cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; i++) {
        ll x,y;
        cin >> x >> y;
        a[i]={x,y};
    }
    long long res = 0;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        vector<Point> vs;
        for (int j = 0; j < n; j++) {
            if (i!=j) {
                vs.push_back(a[j] - a[i]);
            }
        }
        sort(vs.begin(), vs.end(), [&](auto& u, auto& v){
            // x>0, y = 0 as start
            if (u.y >= 0 && v.y < 0) return true;
            if (u.y < 0 && v.y >= 0) return false;
            return cross(u, v) > 0;
        });

        int m = n-1;
        ll tmp = c3(m);
        ll tmp2 = 0;
        for (int j = 0, k = j; j < m; j++) {
            k = max(k, j);
            while (k-j<m && cross(vs[j], vs[k%m]) >= 0) {
                k++;
            }
            k--;
dbg(k,j);
            tmp -= c2(k-j);
            tmp2 += c3(k-j);
        }
        res += tmp;
        ans += tmp2;
    }
    res *= (n-4);
    res /= 2;
    ans = c5(n)*5 - ans;
    assert(ans == res);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
