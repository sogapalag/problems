#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N = 1e9; 
int A,B;

int q(int x, int y) {
    cout << x << ' ' << y << endl;
    string s; cin >> s;
    if (s[0] == 'C') return 0;
    if (s[0] == 'H') return 1;
    if (s[0] == 'M') return 2;
    assert(false);
}

void solve() {
    int x, y;
    int ret = 2;
    // find in
    do {
        x = (int)(rng()%(2*N)) - N;
        y = (int)(rng()%(2*N)) - N;
        ret = q(x,y);
    } while (ret == 2);
    if (ret == 0) return;

    // draw vert,hori line across (x,y)
    // bs 4 boarder, center = (xm,ym)
    int xl,xr,yl,yr;
    {
        int l = -N, r = x;
        while (l < r) {
            int m = l + (r-l)/2;
            ret = q(m,y);
            if (ret == 0) return;
            ret==1 ? r=m : l=m+1;
        }
        xl = r;
    }
    {
        int l = -N, r = y;
        while (l < r) {
            int m = l + (r-l)/2;
            ret = q(x,m);
            if (ret == 0) return;
            ret==1 ? r=m : l=m+1;
        }
        yl = r;
    }
    {
        int l = x, r = N+1;
        while (l < r) {
            int m = l + (r-l)/2;
            ret = q(m,y);
            if (ret == 0) return;
            ret==2 ? r=m : l=m+1;
        }
        xr = r-1;
    }
    {
        int l = y, r = N+1;
        while (l < r) {
            int m = l + (r-l)/2;
            ret = q(x,m);
            if (ret == 0) return;
            ret==2 ? r=m : l=m+1;
        }
        yr = r-1;
    }
    x = xl + (xr-xl)/2;
    y = yl + (yr-yl)/2;
    assert(q(x,y) == 0);
}

// keep in mind what format needed!! might WA!
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    cin >> A >> B;
    for (int t = 1; t <= T; t++) {
        solve();
        //int verdict; cin >> verdict;
        //assert(verdict == 1);
    }
    return 0;
}
