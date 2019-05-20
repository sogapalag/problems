#include <bits/stdc++.h>

using namespace std;


void solve() {
    long long x, y, h, d;
    char op;
    cin >> x >> op >> y;
    cin >> h >> op >> d;
    long long win = 0;
    long long f = -1;
    long long g;
    if (x >= h) {
        f = min(x-h, d);
    }
    f++;
    win += f * (y+1);
    if (x+y >= h) {
        g = max(x+y-h, 0ll);
        g = min(g, d);
        if (f <= g) {
            long long t0 = x+y+1 - h-f;
            long long t1 = x+y+1 - h-g;
            win += (t0+t1)*(t0-t1+1)/2;
        }
    }
    long double res = (long double)win / ((y+1)*(d+1));
    cout << fixed << setprecision(2) << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
