#include <bits/stdc++.h>

using namespace std;

using ll=long long;
const int N = 100005; 
vector<int> X[N], Y[N];
set<pair<int,int>> st;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void gg() {
    cout << "No" << endl; exit(0);
}
void wp() {
    cout << "Yes" << endl; exit(0);
}
void ck(int x, int y) {
    if (st.find({x,y}) == st.end()) gg();
}


// spiral
// impl is heavy, cnt passed should be less code
void solve() {
    int n,m,K;
    cin >> n >> m >> K;
    for (int _ = 0; _ < K; _++) {
        int x,y;
        cin >> x >> y;
        X[x].emplace_back(y);
        Y[y].emplace_back(x);
        st.emplace(x,y);
    }
    for (int i = 1; i <= n; i++) {
        sort(X[i].begin(), X[i].end());
    }
    for (int j = 1; j <= m; j++) {
        sort(Y[j].begin(), Y[j].end());
    }

    int xl = 1, xr = n;
    int yl = 1, yr = m;
    int k = K;
    while (k > 0) {
        auto it = lower_bound(X[xl].begin(), X[xl].end(), yl);
        int y = it==X[xl].end()?yr: (*it)-1;
        y = min(y, yr);
        if (yr > y) {
            ll sq = 1ll*(xr-xl+1)*(yr-y);
            if (sq > k) gg();
            for (int i = xl; i <= xr; i++) {
                for (int j = y+1; j <= yr; j++) {
                    ck(i,j);
                }
            }
            k -= sq;
        }
        yr = y; xl++;
        if (k == 0) wp();
        
        it = lower_bound(Y[yr].begin(), Y[yr].end(), xl);
        int x = it==Y[yr].end()?xr: (*it)-1;
        x = min(x, xr);
        if (xr > x) {
            ll sq = 1ll*(yr-yl+1)*(xr-x);
            if (sq > k) gg();
            for (int i = x+1; i <= xr; i++) {
                for (int j = yl; j <= yr; j++) {
                    ck(i,j);
                }
            }
            k -= sq;
        }
        xr = x; yr--;
        if (k == 0) wp();

        int i = upper_bound(X[xr].begin(), X[xr].end(), yr) - X[xr].begin();
        i--;
        y = i<0?yl:X[xr][i]+1;
        y = max(y, yl);
        if (y > yl) {
            ll sq = 1ll*(xr-xl+1)*(y-yl);
            if (sq > k) gg();
            for (int i = xl; i <= xr; i++) {
                for (int j = yl; j <= y-1; j++) {
                    ck(i,j);
                }
            }
            k -= sq;
        }
        yl = y; xr--;
        if (k == 0) wp();

        int j = upper_bound(Y[yl].begin(), Y[yl].end(), xr) - Y[yl].begin();
        j--;
        x = j<0?xl:Y[yl][j]+1;
        x = max(x, xl);
        if (x > xl) {
            ll sq = 1ll*(yr-yl+1)*(x-xl);
            if (sq > k) gg();
            for (int i = xl; i <= x-1; i++) {
                for (int j = yl; j <= yr; j++) {
                    ck(i,j);
                }
            }
            k -= sq;
        }
        xl = x; yl++;
        if (k == 0) wp();
    }
    wp();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
