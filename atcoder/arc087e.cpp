#include <bits/stdc++.h>

using namespace std;

struct Trie {
    struct Node {
        int ch[2];
        int d;
        Node(int _d) {
            ch[0]=ch[1]=0;
            d = _d;
        }
    };

    vector<Node> t;
    Trie() {
        t.reserve(200'005);
        t.emplace_back(0);
    }
    void add(const string& p) {
        int x = 0;
        for (int i=0; i<(int)p.size(); i++) {
            int k = p[i]-'0';
            if (!t[x].ch[k]) {
                t[x].ch[k] = t.size();
                t.emplace_back(i+1);
            }
            x = t[x].ch[k];
        }
    }
};

// for trie, separate to some complete binary tree.
// sg(k:depth) = k&-k. simulation
void solve() {
    int n; cin >> n;
    long long L; cin >> L;
    Trie t;
    for (int _ = 0; _ < n; _++) {
        string s; cin >> s;
        t.add(s);
    }
    long long sg = 0;
    for (auto& p: t.t) {
        long long k = L - p.d;
        k &= -k;
        if (!p.ch[0]) sg^=k;
        if (!p.ch[1]) sg^=k;
    }
    cout << (sg?"Alice":"Bob");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
