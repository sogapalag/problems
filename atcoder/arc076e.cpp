#include <bits/stdc++.h>

using namespace std;


// after some drawing, note only both end on board matter.
// transform board to a straight line, then each seg must not intersect(can contain). stack maintain.
void solve() {
    int R,C;
    cin >> R >> C;
    auto on_board = [&](int x, int y){
        return x==0 || x==R || y==0 || y==C;
    };
    auto to_line = [&](int x, int y){
        if (y==0) return x;
        if (x==R) return R+y;
        if (y==C) return R+C+R-x;
        assert(x==0);
        return R+C+R+C-y;
    };
    vector<pair<int, int>> a;
    int n; cin >> n;
    for (int _ = 0; _ < n; _++) {
        int x,y,u,v;
        cin >> x >> y >> u >> v;
        if (on_board(x,y) && on_board(u,v)) {
            int i = to_line(x,y);
            int j = to_line(u,v);
            if (i>j) swap(i,j);
            a.emplace_back(i, _);
            a.emplace_back(j, _);
        }
    }
    sort(a.begin(), a.end());
    vector<int> stk;
    for (auto& p: a) {
        if (stk.empty() || stk.back()!=p.second) {
            stk.emplace_back(p.second);
        } else {
            stk.pop_back();
        }
    }
    cout << (stk.empty()?"YES":"NO");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
