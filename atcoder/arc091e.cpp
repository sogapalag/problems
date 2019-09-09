#include <bits/stdc++.h>

using namespace std;


// 5678 34 2 1 pattern. block=b, a=len of first block
void solve() {
    int n,a,b;
    cin >> n >> a >> b;
    if (a + b > n+1) {
        cout << -1; return;
    }
    if (a < (n+b-1)/b) {
        cout << -1; return;
    }
    vector<int> res(n+1);
    int x = n;
    for (int i=a;i>0;i--,x--) {
        res[i] = x;
    }
    if (b > 1) {
        int r = a;
        int len = (n-a)/(b-1);
        int rem = (n-a)%(b-1);
        while (x) {
            int act_len = len + (rem>0?1:0); rem--;
            assert(act_len <= x);
            int l = r+1;
            r = r + act_len;
            for (int i = r; i >= l; i--) {
                res[i] = x--;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << res[i] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
