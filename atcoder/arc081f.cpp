#include <bits/stdc++.h>

using namespace std;
const int N = 2048; 
int a[N][N], b[N][N];
// make sure data in d[1..=n], and >= 0.
template <typename T=int>
T max_area(const vector<T>& d, int n=0) {
    if (!n) n = d.size() - 2;
    assert(n > 0 && d[0] == 0 && d[n+1] == 0);
    vector<int> stk; stk.reserve(n+2);
    stk.emplace_back(0);
    T res = 0;
    for (int i = 1; i <= n+1; i++) {
        while (d[i] < d[stk.back()]) {
            T ht = d[stk.back()]; stk.pop_back();
            T tmp = (ht+1) * (i - stk.back() -1 +1); // h:+1, w:+1. since we consider conjuction
            res = max(res, tmp);
        }
        stk.emplace_back(i);
    }
    return res;
}
// consider 2x2, bad: sum=1 or 3.
// good proof: make toprow leftcol all 1s, then p=(2,2) of course 1, implies grid all 1s.
//
// so find max not contain the mark. aka opsite as 1, find max rect-area 1s.
void solve() {
    int n,m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            a[i][j] = s[j] == '#';
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            b[i][j] = a[i][j]^a[i][j-1]^a[i-1][j-1]^a[i-1][j] ^1;
        }
    }
    int res = max(n,m);
    for (int i = 1; i < n; i++) {
        vector<int> d;
        d.emplace_back(0);
        for (int j = 1; j < m; j++) {
            if (b[i][j]) b[i][j] += b[i-1][j];
            d.emplace_back(b[i][j]);
        }
        d.emplace_back(0);
        int ans = max_area<int>(d);
        res = max(res, ans);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
