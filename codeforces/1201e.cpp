#include <bits/stdc++.h>

using namespace std;
using pi=pair<int, int> ;
#define x first
#define y second
int dx[] = {1,-1,1,-1,2,-2,2,-2};
int dy[] = {2,2,-2,-2,1,1,-1,-1};
const int N = 1024; 
int W[N][N], B[N][N];

// kind of messy
// but keep in mind, x could hunt y iff parity match, and x can goto(y's target) faster than y.
// so basically if x faster than y,(for each own target). decide if y could hunt x
// impl be careful, +/-1 >/>=, </<=. helpful by small case
void solve() {
    int n,m;
    cin >> n >> m;
    pi w, b;
    cin >> w.x >> w.y >> b.x >> b.y;
    
    memset(W, 0x3f, sizeof W);
    memset(B, 0x3f, sizeof B);
    auto build = [&](pi s, int d[N][N]){
        queue<pi> q;
        q.push(s); d[s.x][s.y] = 0;
        while (!q.empty()) {
            int x,y;
            tie(x,y) = q.front(); q.pop();
            for (int _ = 0; _ < 8; _++) {
                int i = x+dx[_];
                int j = y+dy[_];
                if (1<=i&&i<=n && 1<=j&&j<=m) {
                    if (d[i][j] > d[x][y] + 1) {
                        d[i][j] = d[x][y] + 1;
                        q.emplace(i, j);
                    }
                }
            }
        }
    };
    build({n/2,m/2}, W);
    build({n/2+1,m/2}, B);
    //for (int i = 1; i <= n; i++) {
    //    for (int j = 1; j <= m; j++) {
    //        cout << W[i][j] << ' ';
    //    }cout << '\n';
    //}exit(0);
    int tw = W[w.x][w.y];
    int tb = B[b.x][b.y];
//cerr<<tw<<' '<<tb<<endl;
    auto ck = [&](pi u, pi v){
        int x = abs(u.x-v.x);
        int y = abs(u.y-v.y);
        return x+y==3 && (x==1||x==2);
    };
    pi my, enemy;
    auto go = [&](pi u){
        my = u;
        cout << my.x << ' ' << my.y << endl;
        if (my == enemy) exit(0);
        cin >> enemy.x >> enemy.y;
    };

    auto goforit = [&](int d[N][N]){
        while (true) {
            int x,y;
            tie(x,y) = my;
            if (d[x][y] == 0) break;
            if (ck(my,enemy)) go(enemy);
            for (int _ = 0; _ < 8; _++) {
                int i = x+dx[_];
                int j = y+dy[_];
                if (1<=i&&i<=n && 1<=j&&j<=m) {
                    if (d[i][j] == d[x][y]-1) {
                        pi p{i,j};
                        if (!ck(p,enemy)) {
                            go(p); break;
                        }
                    }
                }
            }
        }
    };
    if (tw - tb >= 3 || tw - tb == 1) {
        int t = B[w.x][w.y];
        //cerr<<t<<endl;
        if ((tw-tb)%2 == 1 || tb < t-1) {
            cout << "BLACK" << endl;
            cin >> w.x >> w.y;
            my = b; enemy = w;
            goforit(B);
        } else {
            cout << "WHITE" << endl;
            my = w; enemy = b;
            goforit(B);
            goforit(W);
        }
    } else if (tb - tw >= 2 || tb == tw){
        int t = W[b.x][b.y];
        if ((tb-tw)%2 == 0 || tw < t) {
            cout << "WHITE" << endl;
            my = w; enemy = b;
            goforit(W);
        } else {
            cout << "BLACK" << endl;
            cin >> w.x >> w.y;
            my = b; enemy = w;
            goforit(W);
            goforit(B);
        }
    } else if (tw > tb) {
        assert(tw - tb == 2);
        int t = B[w.x][w.y];
        //cerr<<t<<endl;
        //assert(tb - t >= 1);
        if (tb-(t-1) >= 0) {
            cout << "WHITE" << endl;
            my = w; enemy = b;
            goforit(B);
            goforit(W);
        } else {
            cout << "BLACK" << endl;
            cin >> w.x >> w.y;
            my = b; enemy = w;
            goforit(B);
        }
    } else {
        assert(tb - tw == 1);
        int t = W[b.x][b.y];
        //assert(tw - t >= 2);
        //   #
        // y   x
        //     @
        if (tw-1-(t-1) >= 0) {
            cout << "BLACK" << endl;
            cin >> w.x >> w.y;
            my = b; enemy = w;
            goforit(W);
            goforit(B);
        //   #    #
        // y   # @   x
        //     @ # @
        } else {
            cout << "WHITE" << endl;
            my = w; enemy = b;
            goforit(W);
        }
    }
}
// 14 12
// 8 4 6 4
// y
//   #
// x @
// tw,tb = 1,4

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
