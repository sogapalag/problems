#include <bits/stdc++.h>

using namespace std;

const int N = 100005; 
bool leaf[N];
void solve() {
    vector<map<char,int>> trie; trie.emplace_back();
    int n; cin >> n;
    for (int _ = 0; _ < n; _++) {
        string s; cin >> s;
        int crt = 0;
        for (char c: s) {
            int& to = trie[crt][c];
            if (to == 0) {
                to = trie.size();
                trie.emplace_back();
            }
            crt = to;
        }
        leaf[crt] = true;
    }

    function<multiset<int>(int,int)> dfs = [&](int u, int depth){
        multiset<int> res;
        for (auto& _: trie[u]) {
            char c; int v;
            tie(c, v) = _;
            auto st = dfs(v, depth + 1);
            if (st.size() > res.size()) swap(res, st); // small to large
            for (int x: st) res.insert(x);
        }
        if (leaf[u]) {
            res.insert(depth);
        } else if (!res.empty() && u){
            // greedy make max use current depth
            res.erase(--res.end());
            res.insert(depth);
        }
        return res;
    };
    
    int res = 0;
    for (int depth : dfs(0, 0)) res += depth;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
