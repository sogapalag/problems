#include <bits/stdc++.h>

using namespace std;

struct Game {
    int l, r;
    int L, U;
    Game() {}
    Game(int _l, int _r, int _L, int _U) : l(_l), r(_r), L(_L), U(_U) {}
    bool operator<(const Game& _oth) const {
        return l < _oth.l;
    }
};

// AC. direct impl split game process.
//       | U |
//       |   |
// ______|   |
//           /r
// L ------ //
// ________/l 
void solve() {
    int n,q;
    cin >> n >> q;
    set<Game> s;
    s.emplace(0, n, 0, 0);
    vector<bool> trk(n);
    while (q--) {
        int l,_y; string _;
        cin >> l >> _y >> _; char c = _[0];
        l--;
        assert(l+_y==n); assert(c=='U'||c=='L');
        if(trk[l]) {
            cout << "0\n"; continue;
        }
        trk[l] = true;

        auto g_it = --s.upper_bound(Game{l,0,0,0});
        auto g = *g_it; s.erase(g_it);
        if (c == 'L') {
            cout << (l - g.L + 1) << '\n';
            if (g.l < l) {
                s.emplace(g.l, l, g.L, n-l);
            }
            if (l+1 < g.r) {
                s.emplace(l+1, g.r, g.L, g.U);
            }
        } else {
            cout << (n-l - g.U) << '\n';
            if (g.l < l) {
                s.emplace(g.l, l, g.L, g.U);
            }
            if (l+1 < g.r) {
                s.emplace(l+1, g.r, l+1, g.U);
            }
        }
    }
}

// WA e.g. some U won't be block by some L(since which might blocked early)
void __solve() {
    int n,q;
    cin >> n >> q;
    set<int> X, Y;
    X.emplace(0);
    Y.emplace(0);
    vector<bool> trk(n+1);
    while (q--) {
        int x,y;string _;
        cin >> x >> y >> _; char c = _[0];
        assert(x+y==n+1); assert(c=='U'||c=='L');
        if(trk[x]) {
            cout << "0\n"; continue;
        }
        trk[x] = true;
        if (c == 'L') {
            auto it = --X.upper_bound(x);
            cout << (x - *it) << '\n';
            Y.emplace(y);
        } else {
            auto it = --Y.upper_bound(y);
            cout << (y - *it) << '\n';
            X.emplace(x);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
