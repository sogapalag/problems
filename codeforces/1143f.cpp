#include <bits/stdc++.h>

using namespace std;
using ll=long long;

struct Point {
    ll x, y;
    bool operator <(const Point& _b) { return x < _b.x || (x==_b.x && y < _b.y); }
};

Point operator - (const Point& _a, const Point& _b) {
    return {_a.x - _b.x, _a.y - _b.y};
}
// convex by top points.
void solve() {
    int n; cin >> n;
    vector<Point> p(n);
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        y -= x*x;
        p[i] = {x, y};
    }
    sort(p.begin(), p.end());
    vector<Point> stk; stk.reserve(n);
    auto slope_cmp = [](Point& l1, Point& l2){
        if (!l1.x && !l2.x) {return l1.y < 0 && l2.y > 0;}
        return (ll)l2.x * l1.y < (ll)l1.x * l2.y;
    };

    for (int i = 0; i < n; i++) {
        while (i+1 < n && p[i].x == p[i+1].x) {
            i++;
        }
        int sz = stk.size();
        if (sz < 2) {
            stk.push_back(p[i]);
            continue;
        }
        Point l1 = p[i] - stk[sz-1];
        Point l2 = stk[sz-1] - stk[sz-2];
        while (!slope_cmp(l1, l2)) {
            stk.pop_back();
            sz = stk.size();
            if (sz < 2)  break;
            l1 = p[i] - stk[sz-1];
            l2 = stk[sz-1] - stk[sz-2];
            
        }
        stk.push_back(p[i]);
    }
    int res = stk.size();
    res--;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
