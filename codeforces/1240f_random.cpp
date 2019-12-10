#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 103; 
const int M = 1024; 
const int K = 1024; 

vector<pair<int, int>> es;
int co[M];
int cnt[N][K];

void color(int i, int c) {
    int u,v;
    tie(u,v) = es[i];
    if (co[i] != -1) {
        cnt[u][co[i]]--;
        cnt[v][co[i]]--;
    }
    cnt[u][c]++;
    cnt[v][c]++;
    co[i] = c;
}

void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        int _; cin >> _;
    }
    memset(co, -1, sizeof co);
    for (int i = 0; i < m; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        es.emplace_back(x,y);
        color(i, rng()%k);
    }

    vector<int> nid(n);
    iota(nid.begin(), nid.end(), 0);
    vector<int> eid(m);
    iota(eid.begin(), eid.end(), 0);
    
    auto fix = [&](int u){
        int mi = M, mx = 0;
        for (int i = 0; i < k; i++) {
            mi = min(mi, cnt[u][i]);
            mx = max(mx, cnt[u][i]);
        }
        if (mx - mi <= 2) return false;
        for (int i: eid) {
            int x,y;
            tie(x,y) = es[i];
            if ((u == x || u == y) && cnt[u][co[i]] == mx) {
                color(i, rng()%k);
                return true;
            }
        }
    };

    bool found;
    do {
        found = false;
        shuffle(nid.begin(), nid.end(), rng);
        shuffle(eid.begin(), eid.end(), rng);
        for (int u: nid) {
            while(fix(u)) found = true;
        }
    } while(found);

    for (int i = 0; i < m; i++) {
        cout << co[i]+1 << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
