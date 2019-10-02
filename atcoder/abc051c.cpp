#include <bits/stdc++.h>

using namespace std;


void solve() {
    int x,y,u,v;
    cin >> x >> y >> u >> v;
    //int res = u+v - x-y;
    //res = res*4 + 8;
    //cout << res;
    x = u-x;
    y = v-y;
    string res;
    for (int _ = 0; _ < x; _++) {
        res.push_back('R');
    }
    for (int _ = 0; _ < y; _++) {
        res.push_back('U');
    }
    for (int _ = 0; _ < x; _++) {
        res.push_back('L');
    }
    for (int _ = 0; _ < y; _++) {
        res.push_back('D');
    }
    res.push_back('L');
    for (int _ = 0; _ <= y; _++) {
        res.push_back('U');
    }
    for (int _ = 0; _ <= x; _++) {
        res.push_back('R');
    }
    res.push_back('D');
    res.push_back('R');
    for (int _ = 0; _ <= y; _++) {
        res.push_back('D');
    }
    for (int _ = 0; _ <= x; _++) {
        res.push_back('L');
    }
    res.push_back('U');
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
