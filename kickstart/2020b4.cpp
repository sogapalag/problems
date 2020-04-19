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

double c(int n, int k){
    double res = 1;
    while (k > 0) {
        res *= n--;
        res /= k--;
    }
    return res;
}

// prob........ not ways
void __solve() {
    int n,m;
    cin >> n >> m;
    int x,y,u,v;
    cin >> x >> y >> u >> v;
    double res = 0;
    vector<int> ps,qs;
    auto push = [&](int n, int k, bool rev){
dbg(n,k);
        k = min(k, n-k);
        while (k > 0) {
            if (rev) {
                qs.push_back(n--);
                ps.push_back(k--);
            } else {
                ps.push_back(n--);
                qs.push_back(k--);
            }
        }
    };
    auto calc = [&](){
        double x = 1;
        sort(ps.begin(), ps.end());
        sort(qs.begin(), qs.end());
        assert(ps.size() == qs.size());
        while (true) {
            if (x < 1) {
                if (ps.empty()) break;
                x *= ps.back(); ps.pop_back();
            } else {
                if (qs.empty()) break;
                x /= qs.back(); qs.pop_back();
            }
        }
        while (!ps.empty()) {
                x *= ps.back(); ps.pop_back();
        }
        while (!qs.empty()) {
                x /= qs.back(); qs.pop_back();
        }
        return x;
    };
    for (int _:{0,1}) {
        if (u < n && y > 1) {
            int dx = n-u;
            int dy = y-1;
            int R = u+y-2;
            int S = n-1 + m-1 - R;
            push(R, u, false);
            push(S, n-1-u, false);
            push(R+S, n-1, true);
            double val = calc();
            int step = min(dx, dy);
            res += val;
            for (int _ = 1; _ < step; _++) {
                val *= (R-u);
                val /= (u+1);
                val *= (S - (n-1-u-1));
                val /= (n-1 - u);
                u++;
                res += val;
            }
        }
        swap(x,y);swap(u,v);swap(n,m);
    }
    cout << res << "\n";
}

void ____solve() {
    int n,m;
    cin >> n >> m;
    int x,y,u,v;
    cin >> x >> y >> u >> v;
    vector<int> ps,qs;
    auto push = [&](int n, int k, bool rev){
dbg(n,k);
        k = min(k, n-k);
        while (k > 0) {
            if (rev) {
                qs.push_back(n--);
                ps.push_back(k--);
            } else {
                ps.push_back(n--);
                qs.push_back(k--);
            }
        }
    };
    auto calc = [&](){
        double x = 1;
        sort(ps.begin(), ps.end());
        sort(qs.begin(), qs.end());
        //assert(ps.size() == qs.size());
        while (true) {
            if (x < 1) {
                if (ps.empty()) break;
                x *= ps.back(); ps.pop_back();
            } else {
                if (qs.empty()) break;
                x /= qs.back(); qs.pop_back();
            }
        }
        while (!ps.empty()) {
                x *= ps.back(); ps.pop_back();
        }
        while (!qs.empty()) {
                x /= qs.back(); qs.pop_back();
        }
        return x;
    };
    double res = 0;
    for (int _:{0,1}) {
        if (u < n && y > 1) {
            // stupid, cannot sum it, each step length differ, 2^step
            push(u-1+y-1, y-2, false);
            for (int _ = 1; _ < u; _++) {
                qs.push_back(2);
            }
            res += calc()/2.0;
dbg(res);
        }
        swap(x,y);swap(u,v);swap(n,m);
    }
    cout << res << "\n";
}

using ld = long double;
#define double ld
void solve() {
    int n,m;
    cin >> n >> m;
    int x,y,u,v;
    cin >> x >> y >> u >> v;
    double res = 0;
    vector<double> logfac(n+m);
    for (int i = 1; i < n+m; i++) {
        logfac[i] = logfac[i-1] + log2((double)i);
    }
    const double ln2 = log((double)2);
    
    if(0)for (int _:{0,1}) {
        if (u < n && y > 1) {
            int dx = n-u;
            int dy = y-1;
            int R = u+y-2;
            // dx>dy, bottom prob (u=n) WA, since hit bottom early only 1 way
            int step = min(dx, dy);
            for (int i = 0; i < step; i++) {
                double x = logfac[R] - logfac[R-u-i] - logfac[u+i] - R;
                //res += pow((double)2.0, x);
                res += exp(ln2*x);
            }
        }
        swap(x,y);swap(u,v);swap(n,m);
    }
    // hori
    for (int _:{0,1}) {
        if (u < n && y > 1) {
            for (int k = 0; k <= y-2; k++) {
                double tmp = logfac[u-1 + k] - logfac[u-1] - logfac[k] - (u+k);
                res += exp(ln2*tmp);
            }
        }
        swap(x,y);swap(u,v);swap(n,m);
    }
    cout << res << "\n";
}

// painful.. not doing much with float, most MOD..
// and thinking in a wrong way. not counting path.
//   is counting prob, which is different, hit-boarder would result 1 possbility
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(10);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
