#include <bits/stdc++.h>

using namespace std;

int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
const int N = 1024; 
bool trk[N][N];
void solve() {
    int n,m;
    cin >> n >> m;
    vector<string> s(n);
    for (auto& x: s) cin >> x;
    vector<int> R(n+1), C(m+1);

    int compo = 0;
    auto bfs = [&](int i, int j){
        ++compo;
        queue<pair<int,int>> q;
        q.emplace(i,j);
        trk[i][j] = true;
        int mx = i, Mx = i;
        int my = j, My = j;
        while (!q.empty()) {
            int x,y;
            tie(x,y) = q.front(); q.pop();
            mx = min(mx, x);
            Mx = max(Mx, x);
            my = min(my, y);
            My = max(My, y);
            for (int _ = 0; _ < 4; _++) {
                int i = x + dx[_];
                int j = y + dy[_];
                if (0<=i&&i<n && 0<=j&&j<m && s[i][j]=='#' && !trk[i][j]) {
                    trk[i][j] = true;
                    q.emplace(i,j);
                }
            }
        }
        R[mx]++; R[Mx+1]--;
        C[my]++; C[My+1]--;
    };

    // each row/col all # continous
    for (int i = 0; i < n; i++) {
        int l = 0;
        while (l < m && s[i][l] != '#') {
            l++;
        }
        int r = m-1;
        while (r >= 0 && s[i][r] != '#') {
            r--;
        }
        if (l < r) {
            for (int j = l; j < r; j++) {
                if (s[i][j] != '#') {
                    cout << -1; return;
                }
            }
        }
    }
    for (int j = 0; j < m; j++) {
        int l = 0;
        while (l < n && s[l][j] != '#') {
            l++;
        }
        int r = n-1;
        while (r >= 0 && s[r][j] != '#') {
            r--;
        }
        if (l < r) {
            for (int i = l; i < r; i++) {
                if (s[i][j] != '#') {
                    cout << -1; return;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j]=='#' && !trk[i][j]) bfs(i,j);
        }
    }

    int r = 0;
    for (int i = 0; i < n; i++) {
        R[i+1] += R[i];
        r += R[i]==0;
    }
    int c = 0;
    for (int j = 0; j < m; j++) {
        C[j+1] += C[j];
        c += C[j]==0;
    }
    // remain rect no (r>0,c=0) situation, (cannot assign South)
    if (r+c > 0 && (r==0||c==0)) {
        cout << -1; return;
    }

    cout << compo;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
