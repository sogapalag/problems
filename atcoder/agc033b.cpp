#include <bits/stdc++.h>

using namespace std;


// row-col independent
// back compute valid rigion.
void solve() {
    int h, w, n;
    cin >> h >> w >> n;
    int x, y;
    cin >> x >> y;
    string S(n+1, '.'), T(n+1, '.');
    cin >> &S[1];
    cin >> &T[1];
    int l = 1, r = w;
    bool flag = true;
    for (int i = n; i >= 1; i--) {
        if (T[i] == 'L' && r < w) {
            r++;
        }
        if (T[i] == 'R' && l > 1) {
            l--;
        }
        if (S[i] == 'R') {
            r--;
        }
        if (S[i] == 'L') {
            l++;
        }
        if (l > r) {
            flag = false; break;
        }
    }
    if (!flag || y > r || y < l) {
        cout << "NO"; return;
    }
    l = 1, r = h;
    flag = true;
    for (int i = n; i >= 1; i--) {
        if (T[i] == 'U' && r < h) {
            r++;
        }
        if (T[i] == 'D' && l > 1) {
            l--;
        }
        if (S[i] == 'D') {
            r--;
        }
        if (S[i] == 'U') {
            l++;
        }
        if (l > r) {
            flag = false; break;
        }
    }
    if (!flag || x > r || x < l) {
        cout << "NO"; return;
    }
    cout << "YES";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
