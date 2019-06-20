#include <bits/stdc++.h>

using namespace std;

using ll=long long;

struct Point {
    ll x, y;
    int id;
    Point() {}
    Point(ll _x, ll _y, int _id) : x(_x), y(_y), id(_id) {}
};
Point operator-(const Point& u, const Point& v) {
    return {u.x - v.x, u.y - v.y, -1};
}
ll cross(const Point& u, const Point& v) {
    return u.x * v.y - u.y * v.x;
}


// pick point in most side, e.g. mini y
// thus remain points in half-side, pick one angle min or max by s[i], it will make nex rot valid.
// this sortness, by swap sort by comp cross. cos angle with double may cause accuracy error.
void solve() {
    int n; cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
        a[i].id = i+1;
    }
    string s(n, '#');
    cin >> &s[1];
    
    for (int i = 1; i < n; i++) {
        if (a[i].y < a[0].y) {
            swap(a[i], a[0]);
        }
    }
    function<void (int)> find = [&](int i){
        if (i == n) return;
        if (s[i] == 'L') {
            for (int j = i+1; j < n; j++) {
                if (cross(a[j]-a[i-1], a[i]-a[i-1]) > 0)
                    swap(a[j], a[i]);
            }
        } else {
            for (int j = i+1; j < n; j++) {
                if (cross(a[j]-a[i-1], a[i]-a[i-1]) < 0)
                    swap(a[j], a[i]);
            }
        }
        find(i+1);
    };
    find(1);
    for (auto& x: a) {
        int res = x.id;
        cout << res << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
