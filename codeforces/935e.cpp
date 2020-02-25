#include <bits/stdc++.h>

using namespace std;

const int N = 1e4+10; 
int mx[N][111];
int mi[N][111];
void solve() {
    string s; cin >> s;
    int n = s.size();
    int cnt = 0;
    vector<int> leaf(n, -1);
    vector<int> pa(n, -1);
    vector<vector<int>> g(n);
    int i = 0;
    function<int()> parse = [&](){
        if (s[i]!='(') {
            leaf[++cnt] = s[i++]-'0';
            return cnt;
        } else {
            assert(s[i++] == '(');
            int l = parse();
            assert(s[i++] == '?');
            int u = ++cnt;
            int r = parse();
            assert(s[i++] == ')');
            pa[l] = pa[r] = u;
            g[u].push_back(l);
            g[u].push_back(r);
            return u;
        }
        assert(false);
    };
    int root = parse();

    int P, M;
    cin >> P >> M;
    bool p = P<=M;
    int m = min(P, M);
    
    memset(mx, 0xc0, sizeof mx);
    memset(mi, 0x3f, sizeof mi);
    function<void(int)> dfs = [&](int u){
        if (leaf[u] != -1) {
            mx[u][0] = mi[u][0] = leaf[u];
            //cerr<<u<<' '<< leaf[u]<<endl;
            return;
        }
        int l = g[u][0], r = g[u][1];
        dfs(l); dfs(r);
        //cerr<<l<<' '<< u << ' '<< r<<endl;
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j+i <= m; j++) {
                mx[u][i+j + (p)] = max(mx[u][i+j+(p)], mx[l][i] + mx[r][j]);
                mx[u][i+j +(!p)] = max(mx[u][i+j+(!p)],mx[l][i] - mi[r][j]);
                mi[u][i+j + (p)] = min(mi[u][i+j+(p)], mi[l][i] + mi[r][j]);
                mi[u][i+j +(!p)] = min(mi[u][i+j+(!p)],mi[l][i] - mx[r][j]);
            }
        }
    };
    dfs(root);
    cout << mx[root][m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
