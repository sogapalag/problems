#include <bits/stdc++.h>

using namespace std;

// impl painful, maybe abbr p32, or hash it
void solve() {
    int n; cin >> n;
    vector<vector<int>> a(n-2, vector<int>(3));
    map<pair<int,int>, set<int>> mp;
    vector<vector<pair<int, int>>> es(n-2);
    for (int i = 0; i < n-2; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        //for (int _ = 0; _ < 3; _++) {
        //    cnt[a[i][_]]++;
        //}
        sort(a[i].begin(), a[i].end());
        mp[{a[i][0],a[i][1]}].emplace(i);
        mp[{a[i][0],a[i][2]}].emplace(i);
        mp[{a[i][1],a[i][2]}].emplace(i);
        es[i].emplace_back(a[i][0],a[i][1]);
        es[i].emplace_back(a[i][0],a[i][2]);
        es[i].emplace_back(a[i][1],a[i][2]);
    }
    vector<vector<int>> g(n+1);
    vector<int> cnt(n-2);
    for (auto it = mp.begin(); it != mp.end(); it++) {
        if (it->second.size()==1) {
            int x,y;
            tie(x,y)=it->first;
            g[x].push_back(y);
            g[y].push_back(x);
            cnt[*(it->second.begin())]++;
        }
    }
    // those n segs adj-only 1 tri. are sides
    vector<int> p;
    vector<bool> trk(n+1);
    function<void(int)> dfs = [&](int u){
        trk[u]=1;
        p.push_back(u);
        for (int v:g[u])if(!trk[v]){
            dfs(v);
        }
    };
    dfs(1);
    for(int x:p){
        cout << x<<' ';
    }cout << '\n';

    // remove #segs>=2. keep update
    set<int> s;
    for (int i = 0; i < n-2; i++) {
        if (cnt[i]>=2) s.insert(i);
    }
    vector<int> q;
    while (q.size()<n-2) {
        int i = *s.begin();
        q.push_back(i); s.erase(i);
        for (auto& e: es[i]) {
            mp[e].erase(i);
            if(mp[e].size()==1) {
                int j = *mp[e].begin();
                cnt[j]++;
                if (cnt[j]>=2) s.insert(j);
            }
        }
    }
    for (int x:q){
        cout << x+1<<' ';
    }cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;cin >> t;
    while(t--)solve();
    cout << endl;
}
