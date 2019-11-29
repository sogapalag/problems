#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p;
    
    Dsu(int _n) { n = _n; p.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        p[y] = x; return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};

bool trk[26];
bool a[26];

void solve() {
    int n; cin >> n;
    Dsu d(26);
    for (int _ = 0; _ < n; _++) {
        memset(a, 0, sizeof a);
        string s; cin >> s;
        for (char c: s) a[c-'a'] = trk[c-'a'] = 1;
        for (int i = 0; i < 26; i++) {
            if (a[i]) {
                for (int j = 0; j < 26; j++) {
                    if (j!=i && a[j]) {
                        d.join(i,j);
                    }
                }
            }
        }
    }
    set<int> s;
    for (int i = 0; i < 26; i++) {
        if (trk[i]) {
            s.insert(d.find(i));
        }
    }
    cout << s.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
