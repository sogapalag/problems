#include <bits/stdc++.h>

using namespace std;

#define dbg(x) cerr<<#x<<" = "<<(x)<<endl;

void solve() {
    int n, r, c, x, y;
    cin >> n >> r >> c >> x >> y;
    struct Node {
        int U,D,L,R;
    };
    vector<Node> a(n+1);
    a[0] = {0,0,0,0};
    const long long N = 1000000; 
    auto com = [](int u, int v){
        return N*u + v;
    };
    map<long long, int> id;
    id[com(x, y)] = 0;
    int cx = x, cy = y;
    auto upd = [&](long long p){
        int x = p/N, y = p%N;
        int j = id[p];
        int U=x, D=x, L=y, R=y;
        long long up = p;
        long long dp = p;
        long long lp = p;
        long long rp = p;
        //dbg(p);
        while (1) {
            int du = a[id[up]].U; 
            //dbg(du);
            if (du) {
                U -= du;
                up = com(U, y);
                if (id.find(up) == id.end()) break;
            } else {
                up=com(U-1, y);
                if (id.find(up) != id.end()) {
                    U--;
                }else{
                    break;
                }
            }
        }
        while (1) {
            int dd = a[id[dp]].D; 
            //dbg(dd);
            if (dd) {
                D += dd;
                dp = com(D, y);
                if (id.find(dp) == id.end()) break;
            } else {
                dp=com(D+1, y);
                if (id.find(dp) != id.end()) {
                    D++;
                }else{
                    break;
                }
            }
        }
        while (1) {
            int dl = a[id[lp]].L; 
            //dbg(dl);
            if (dl) {
                L -= dl;
                lp = com(x, L);
                if (id.find(lp) == id.end()) break;
            } else {
                lp=com(x, L-1);
                if (id.find(lp) != id.end()) {
                    L--;
                }else{
                    break;
                }
            }
        }
        while (1) {
            int dr = a[id[rp]].R; 
            //dbg(dr);
            if (dr) {
                R += dr;
                rp = com(x, R);
                if (id.find(rp) == id.end()) break;
            } else {
                rp=com(x, R+1);
                if (id.find(rp) != id.end()) {
                    R++;
                }else{
                    break;
                }
            }
        }
        //dbg(U); dbg(D);
        int i_u = id[com(U, y)];
        int i_d = id[com(D, y)];
        int i_l = id[com(x, L)];
        int i_r = id[com(x, R)];
        a[i_u].D = D-U;
        a[i_d].U = D-U;
        a[i_l].R = R-L;
        a[i_r].L = R-L;
    };
    for (int i = 1; i <= n; i++) {
        char s; cin >> s;
        long long p;
        int tx = cx, ty = cy;
        if (s == 'N') {
            cx--;
            p = com(cx, cy);
            if (id.find(p) == id.end()) {
                id[p] = i;
                a[i] = {0, 0, 0, 0};
            } else {
                int j = id[p];
                cx -= a[j].U + 1;
                p = com(cx, cy);
                id[p] = i;
            }
        }
        if (s == 'E') {
            cy++;
            p = com(cx, cy);
            if (id.find(p) == id.end()) {
                id[p] = i;
                a[i] = {0, 0, 0, 0};
            } else {
                int j = id[p];
                cy += a[j].R + 1;
                p = com(cx, cy);
                id[p] = i;
            }
        }
        if (s == 'S') {
            cx++;
            p = com(cx, cy);
            if (id.find(p) == id.end()) {
                id[p] = i;
                a[i] = {0, 0, 0, 0};
            } else {
                int j = id[p];
                cx += a[j].D + 1;
                p = com(cx, cy);
                id[p] = i;
            }
        }
        if (s == 'W') {
            cy--;
            p = com(cx, cy);
            if (id.find(p) == id.end()) {
                id[p] = i;
                a[i] = {0, 0, 0, 0};
            } else {
                int j = id[p];
                cy -= a[j].L + 1;
                p = com(cx, cy);
                id[p] = i;
            }
        }
        upd(p);
        if (i == n) {
            int rx = p/N, ry = p%N;
            cout << rx << ' ' << ry;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
