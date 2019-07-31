#include <bits/stdc++.h>

using namespace std;

vector<bool> valid;

void kmp_pre(string& s, string& p){
    //int b[P]; b[0]=-1;// kmp backup table
    int l = p.size();
    vector<int> b(l+1);
    b[0] = -1;
    int j = -1;

    for (int i=0; i < l;){
        while (j >= 0 && p[i] != p[j])
            j = b[j];
        i++; j++;
        b[i] = j;
    }

    int n = s.size();
    int len = 0;
    for (int i=0; i<n+l; i++){
        char x = s[i%n];
        int j = len;
        while (j >= 0 && x != p[j])
            j = b[j];
        len = ++j;
        if (len == l) {
            valid[i-l+1] = true;
        }
    }
}

// s(n+m), t(m), preprocess start at s_[0,n) is a valid match
// then i->j a DAG, self-loop/cycle means INF path, output -1.
// from indeg = 0, as start, bfs the max length. actually graph is lines, since i-> at most one node.
void solve() {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    valid.assign(n, false);
    kmp_pre(s, t);
   // for (bool x: valid) {
   //     cout << (x?'T':'F');
   // }
    
    vector<vector<int>> g(n);
    vector<int> indeg(n, -1);
    vector<int> d(n, 0);
    for (int i = 0; i < n; i++) {
        if (valid[i]) {
            indeg[i] = 0;
            d[i] = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        int j = (i+m)%n;
        if (valid[i] && valid[j]) {
            if (i == j) {
                cout << -1; return; //self-loop
            }
            g[i].emplace_back(j);
            indeg[j]++;
        }
    }
    vector<int> trk(n, false);
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) {
            q.push(i);
            trk[i] = true;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& v: g[u]) {
            d[v] = 1 + d[u];
            trk[v] = true;
            q.push(v);
        }
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (valid[i] && !trk[i]) {
            cout << -1; return; // cycle
        }
        res = max(res, d[i]);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
