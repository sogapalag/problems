#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, k;
    cin >> n >> k;
    string s; cin >> s;
    int sum = 0, cnt = 0;//flip, LR / RL
    int len = 1;//consective
    for (int i = 1; i < n; i++) {
        if (s[i] == s[i-1]) {
            len++;
        } else {
            sum += len-1;
            len = 1;
            cnt++;
        }
    }
    sum += len-1;
    int res = sum + min(k*2, cnt);// one op dec at most two flip
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
