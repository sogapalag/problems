#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int A;
int n,m;
int a[25][55];
int r,c;
int cnt;
int digged;

//#define LOCAL
void q(int i, int j) {
    cnt++;
#ifdef LOCAL
    r = i + (rng()%3)-1;
    c = j + (rng()%3)-1;
    digged += a[r][c] == 0;
    if (digged == A) r=0,c=0;
#else
    cout << i << ' ' << j << endl;
    cin >> r >> c;
#endif
    a[r][c] = 1;
}


// a naive. pick max neib
// 1200~1500
void __solve() {
    cin >> A;
    if (A==20) n=4,m=5;
    else n=4,m=50;
    memset(a, 0, sizeof a);
    cnt = 0;
    digged = 0;
    do {
        int mx = 0, x,y;
        for (int i = 2; i < n; i++) {
            for (int j = 2; j < m; j++) {
                int hole = 0;
                for (int ii:{i-1,i,i+1}){
                    for (int jj:{j-1,j,j+1}) {
                        hole += a[ii][jj] == 0;
                    }
                }
                if (mx < hole) {
                    hole = mx; x=i,y=j;
                }
            }
        }
        q(x,y);
    } while (r != 0);
    cerr<<cnt<<endl;
}

// recall coupon collector. E = n H(n). H(9) ~ 2.828
// i.e. for 3x3 region, 3*9 is fine.
// we just divide it 4x3, thus < 5 = 1000/200
// ~ 700
void solve() {
    cin >> A;
    if (A==20) n=4,m=5;
    else n=4,m=50;
    memset(a, 0, sizeof a);
    cnt = 0;
    digged = 0;
    vector<int> cols;
    for (int i = 2; i < m; i+=3) {
        cols.push_back(i);
    }
    cols.push_back(m-1);

    auto full = [&](int j){
        for (int i = 1; i <= 4; i++) {
            for (int jj:{j-1,j,j+1}) {
                if (!a[i][jj]) return false;
            }
        }
        return true;
    };
    for (int j:cols) {
        do {
            int mx = 0,x;
            for (int i:{2,3}) {
                int hole = 0;
                for (int ii:{i-1,i,i+1}){
                    for (int jj:{j-1,j,j+1}) {
                        hole += a[ii][jj] == 0;
                    }
                }
                if (mx < hole) {
                    hole = mx; x=i;
                }
            }
            q(x,j);
        } while (r != 0 && !full(j)); // end r=c=0
    }
    cerr << cnt << endl;
}

// keep in mind what format needed!! might WA!
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        solve();
        //int verdict; cin >> verdict;
        //assert(verdict == 1);
    }
    return 0;
}
