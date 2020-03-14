#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int L = 30; 
void solve() {

    vector<ll> pw(L+1);
    pw[0] = 1;
    for (int i = 1; i <= L; i++) {
        pw[i] = pw[i-1]*3;
    }

    // 3 2 4 2
    // pw[i] may not between, depend y0,y1.
    auto f = [&](ll x0, ll x1){
        for (int i = L-1; i >= 0; x0%=pw[i], x1%=pw[i], i--) {
            int b0 = (x0 / pw[i])%3;
            int b1 = (x1 / pw[i])%3;
            if (b0 != b1) break;
            if (b0 != 1) continue;
            if (x0 > x1) swap(x0,x1);
            return 2ll * min(2ll*pw[i] - x1, x0 - (pw[i]-1));
        }
        return 0ll;
    };

    auto g = [&](ll x0, ll x1, ll y0, ll y1){
        for (int i = L-1; i >= 0; x0%=pw[i], x1%=pw[i], y0%=pw[i], y1%=pw[i], i--) {
            int b0 = (x0/pw[i]);
            int b1 = (x1/pw[i]);
            int c0 = (y0/pw[i]);
            int c1 = (y1/pw[i]);
            if (b0 != b1 && c0 != c1) return 0ll;
            if (b0 == b1 && c0 == c1) continue;
            if (c0 == c1) {
                swap(x0,y0);
                swap(x1,y1);
            }
            if (y0 > y1) {
                swap(y0,y1);
            }
            bool exist = (c0==0 && c1==2);
            for (; i >= 0; x0%=pw[i], x1%=pw[i], i--) {
                int b0 = (x0 / pw[i])%3;
                int b1 = (x1 / pw[i])%3;
                if (b0 != b1) return 0ll;
                if (b0 != 1 || !exist) {
                    y0%=pw[i], y1%=pw[i];
                    if(i) {
                        int c0 = (y0/pw[i-1]);
                        int c1 = (y1/pw[i-1]);
                        exist = exist || !(c0==2&&c1==0);
                    }
                    continue;
                }
                if (x0 > x1) swap(x0,x1);
                return 2ll * min(2ll*pw[i] - x1, x0 - (pw[i]-1));
            }
            return 0ll;
        }
        return 0ll;
    };

    // ignore above WA and ugly f,g.. 
    // the key is note there're many white, we can "almost" achieve x1-x0+y1-y0, i.e. mahattan
    // Claim 1: if neither x,y in same region(that bit !=)  h = 0, i.e. we can achieve mahattan.
    // wlog let moment x same, but y differ
    // Claim 2: in y direction we don't need to waste(go-anti)
    //   Claim 2.1: if some moment x !=, then cost = 0
    // Claim 3: in x direction we waste only because by some BLACK-BLOCK with pw[i]
    //   the time x == 1
    //
    // above Claimes based on intuition that we can always make some turn since there're many white. 
    auto h = [&](ll x0, ll x1, ll y0, ll y1){
        if (x0>x1)swap(x0,x1);
        if (y0>y1)swap(y0,y1);
        // let x same.
        if (x1-x0 > y1-y0) {
            swap(x0,y0);
            swap(x1,y1);
        }
        for (int i = L-1; i >= 0; i--) {
            if (x0/pw[i] == x1/pw[i] && (x0/pw[i])%3 == 1) {
                // check is there indeed a BLACK-pw[i]
                // trick case y0 = 0 222
                //            y1 = 1 000
                // dist > 1 is simpler
                if (y1/pw[i] - y0/pw[i] > 1) {
                    // waste left or right
                    return 2ll*min(x0 - x0/pw[i]*pw[i] + 1, (x0/pw[i] + 1)*pw[i] - x1);
                }
            }
        }
        return 0ll;
    };

    int q; cin >> q;
    while (q--) {
        ll x,y,u,v;
        cin >> x >> y >> u >> v;
        x--;y--;u--;v--;
        ll res = abs(x-u) + abs(y-v);
        //res += f(x,u) + f(y,v);
        //res += g(x,u,y,v);
        res += h(x,u,y,v);
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
