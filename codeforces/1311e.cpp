#include <bits/stdc++.h>

using namespace std;

const int N = 5003; 
int L[N], U[N];
int lb(int n){
    if (n<=1) return 0;
    if (L[n]) return L[n];
    int x = n/2;
    int y = n - x - 1;
    return L[n] = x+y+lb(x) + lb(y);
}
int ub(int n){
    return n*(n-1)/2;
}
void prep() {
    for (int i = 2; i < N; i++) {
        L[i] = lb(i);
        U[i] = ub(i);
    }
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
void solve() {
    int n,d;
    cin >> n >> d;
    if (L[n]>d || d>U[n]) {
        cout << "NO\n"; return;
    }
    cout << "YES\n";
    vector<int> pa(n);
    int cnt = 1;
    // try random divi, since there should be many candidates (by intuition).
    function<void(int,int,int)> divi = [&](int u, int n, int d){
        if (n <= 1) return;
        int x,dx,y,dy;
        while(true) {
            x = rng()%n;
            dx = L[x] + rng()%(U[x] - L[x] + 1);
            y = n - 1 - x;
            dy = d-(n-1) - dx;
            if (L[y] <= dy && dy <= U[y]) break;
        }
        if (x) {
            pa[cnt++] = u;
            divi(cnt-1, x, dx);
        }
        if (y) {
            pa[cnt++] = u;
            divi(cnt-1, y, dy);
        }
    };
    divi(0, n, d);
    for (int i = 1; i < n; i++) {
        cout << pa[i]+1 << ' ';
    }cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    prep();
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
