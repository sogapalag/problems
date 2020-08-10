#include <bits/stdc++.h>

using namespace std;

pair<int,int> query(vector<int> a) {
    cout << "? " << a.size() << '\n';
    for (int x: a) {
        cout << x+1 << ' ';
    }
    cout << endl;
    int x,d;
    cin >> x >> d;
    --x;
    return {x,d};
}

// caterpillar, extend len with ceil(L/2, 4/L, 8/L,...)
void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        --x;--y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    int head, tail;
    int L;
    vector<bool> body(n);
    {
        vector<int> a(n);
        iota(a.begin(), a.end(), 0);
        tie(head, L) = query(a);
        tail = head;
        body[head] = true;
    }
    vector<int> pa(n), depth(n);
    function<void(int,int)> dfs = [&](int u, int p){
        pa[u] = p;
        for (int v: g[u])if(v!=p){
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    };
    int len = 0;
    while (len < L) {
        int extend = (L-len+1)/2;
        vector<int> a;
        for (int r:{head,tail}) {
            depth[r] = 0; dfs(r,-1);
            for (int i = 0; i < n; i++) {
                if (!body[i] && depth[i] == extend) {
                    a.push_back(i);
                }
            }
        }
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        int x,d;
        tie(x,d) = query(a);
        assert(d == L);

        depth[x] = 0; dfs(x, -1);
        if (depth[head] > depth[tail]) {
            swap(head, tail);
        }
        assert(extend == depth[head]);
        len += depth[head];
        while (head != x) {
            body[head = pa[head]] = true;
        }
    }
    cout << "! " << head+1 << ' ' << tail+1 << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
        string verdict;
        cin >> verdict;
        assert(verdict[0] == 'C');
    }
    return 0;
}
