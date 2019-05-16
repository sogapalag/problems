#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+6; 
const int INF = 0x3f3f3f3f;

// foreach distinc x, find occur left/right
// use which to find prefix[x], i.e. [1..x] sorted with end index. /INF means unsorted.
void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> fst(N, 0);
    vector<int> lst(N, 0);
    for (int i = 1; i <= n; i++) {
        int a; cin >> a;
        if (!fst[a]) fst[a] = i;
        lst[a] = i;
    }
    vector<int> pre(N);
    pre[0] = 0;
    for (int a = 1; a <= x+1; a++) {
        if (!fst[a]) {
            pre[a] = pre[a-1];
        } else if (pre[a-1] < fst[a]) {
            pre[a] = lst[a];
        } else {
            pre[a] = INF;
        }
    }
    vector<int> suf(N);
    suf[x+1] = INF;
    for (int a = x; a >= 0; a--) {
        if (!lst[a]) {
            suf[a] = suf[a+1];
        } else if (lst[a] < suf[a+1]) {
            suf[a] = fst[a];
        } else {
            suf[a] = 0;
        }
    }
    int r = 1;
    long long res = 0;
    for (int l = 1; l <= x; l++) {
        r = max(r, l); // prevent l>r
        // find fisrt valid r
        while (r <= x && pre[l-1] >= suf[r+1]) {
            r++;
        }
        res += x+1-r;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
