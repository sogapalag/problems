#include <bits/stdc++.h>

using namespace std;


// first note only info is (mi, delta)
// then one need find some sortness
// after some try, the correct contruct is as below.
// split by d>0 into two group.
// wlog for (d>0)a, then sort it by mi. one can see larger mi first. proof by swap. omit
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a,b;
    int sum = 0;
    for (int _ = 0; _ < n; _++) {
        string s; cin >> s;
        int x = 0, mi = 0;
        for (char c:s) {
            if (c=='(')x++;
            else x--;
            mi = min(mi, x);
        }
        sum += x;
        if (x > 0) a.emplace_back(mi, x);
        else b.emplace_back(mi-x, -x); // !!dual form, not (mi,x).
    }
    if (sum != 0) {
        cout << "No"; return;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    auto ck = [](auto a){
        int x = 0;
        for (auto& p: a) {
            int mi,d;
            tie(mi,d) = p;
            if (x+mi<0) {
                return false;
            }
            x += d;
        }
        return true;
    };
    if (ck(a)&&ck(b)) {
        cout << "Yes";
    } else {
        cout << "No";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
