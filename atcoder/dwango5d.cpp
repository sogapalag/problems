#include <bits/stdc++.h>

using namespace std;

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}

const int N = 1024; 
int cnt[N][N];
int a[N<<1][N<<1];
int b[N<<1][N<<1];

// let n be max that cnt_ij<=n*n
// def two type, a  z< cnt <= n*n.
//               b  p< cnt <= z.
// only there points matter, since other points, must in a square with length (n-1)D
// for a type, it behave like cnt=n*n, so we must conclude all
// for b type, the points like, e.g. cnt=5 
//              .  
//           .  .
//           .  .
// we could conclude it by hori it or verti it, optimal is choose min exceed length.
// thus for i,j,d. the conclude shape like
//       ----
//       |  |
//       |  ----
//       |     |
//       ------|
void solve() {
    int n, D;
    cin >> n >> D;
    for (int _ = 0; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x%=D;
        y%=D;
        cnt[x][y]++;
    }
    n = 0;
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < D; j++) {
            int k = 0;
            while (k*k < cnt[i][j]) {
                k++;
            }
            n = max(n,k);
        }
    }
    int z = (n-1)*n;
    int p = (n-1)*(n-1);
    int Z = 0;
    int P = 0;
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < D; j++) {
            if (cnt[i][j] > z) {
                Z++;
                int x=i+1, y=j+1;
                a[x][y] = a[x][y+D] = a[x+D][y] = a[x+D][y+D] = 1;
            } else if (cnt[i][j] > p) {
                P++;
                int x=i+1, y=j+1;
                b[x][y] = b[x][y+D] = b[x+D][y] = b[x+D][y+D] = 1;
            }
        }
    }
    const int LIM = D<<1; 
    for (int i = 1; i <= LIM; i++) {
        for (int j = 1; j <= LIM; j++) {
            a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
            b[i][j] += b[i-1][j] + b[i][j-1] - b[i-1][j-1];
        }
    }
    auto sum = [&](int i, int j, int d){
        return a[i+d][j+d] - a[i][j+d] - a[i+d][j] + a[i][j];
    };
    auto sum_b = [&](int i, int j, int d){
        return b[i+d][j+d] - b[i][j+d] - b[i+d][j] + b[i][j];
    };
    auto cover = [&](int i, int j, int d){
        return P - sum_b(i+d,j+d,D-d);
    };

    if (D == 1) {
        cout << (n-1); return;
    }

    int res = D;
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < D; j++) {
            int tmp = bs_first<int>(1, D, [&](int d){
                    return sum(i,j,d) >= Z;
                    });
            int cov = bs_first<int>(1, D, [&](int d){
                    return cover(i,j,d) >= P;
                    });
            tmp = max(tmp, cov);
            res = min(res, tmp);
        }
    }
    res += (n-1)*D - 1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
