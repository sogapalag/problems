#include <bits/stdc++.h>

using namespace std;
using pd = pair<double,double>;
#define fi first
#define se second

const double EPS = 1e-8; 
// WA, don't know why
void __solve() {
    int n; double P;
    cin >> n >> P;
    vector<pd> seg;
    seg.emplace_back(0, 0);
    auto shrink = [&](auto& a){
        sort(a.begin(), a.end());
        while (!a.empty() && a.back().fi > P+EPS) {
            a.pop_back();
        }
        vector<pd> b;
        double l=0,r=0;
        for (auto& _: a) {
            double x,y;
            tie(x,y) = _;
            if (x <= r) r = max(r, y);
            else {
                b.emplace_back(l, r);
                l = x, r = y;
            }
        }
        b.emplace_back(l, r);
        return b;
    };
    for (int _ = 0; _ < n; _++) {
        double x,y;
        cin >> x >> y;
        if (x > y) swap(x, y);
        double z = sqrt(x*x + y*y);
        vector<pd> a;
        a.emplace_back(2*(x+y), 2*(x+y));
        a.emplace_back(4*x+2*y, 2*(x+y+z));
        //auto now = seg;
        vector<pd> now;
        for (auto& s: seg) {
            for (auto& t: a) {
                now.emplace_back(s.fi+t.fi, s.se+t.se);
            }
        }
        seg = shrink(now);
    }
    double res = min(P, seg.back().se);
    cout << res << '\n';
}

// key: each valid seg's left is integer
// dp[l]=r, indicate l..r is valid
void solve() {
    int n,P;
    cin >> n >> P;
    vector<pair<int, int>> a(n);
    int base = 0;
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        if (x > y) swap(x,y);
        x*=2, y*=2;
        a[i] = {x,y};
        base += x+y;
    }
    P -= base;
    const int LIM = min(2*250*n, P); // 2*x
    vector<double> dp(LIM + 1, -1);
    dp[0] = 0;
    for (auto& _: a) {
        int x,y;
        tie(x,y) = _;
        double z = sqrt(x*x+y*y);
        for (int l = LIM-x; l >= 0; l--) {
            if (dp[l] < -0.5) continue;
            dp[l+x] = max(dp[l+x], dp[l] + z);
        }
    }
    double res = 0;
    for (double r: dp) {
        res = max(res, r);
    }
    res = min(res, (double)P);
    res += base;
    cout << res << "\n";
}

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
