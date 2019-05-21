#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n;
    while (cin >> n) {
        if (!n) break;
        vector<int> a(n+1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        vector<int> stk; stk.reserve(n);
        int cnt = 1;
        bool flag = true;
        for (int i = 1; i <= n; i++) {
            if (a[i] == cnt) {
                cnt++;
                continue;
            }
            if (stk.empty()) {
                stk.push_back(a[i]);
            } else if (stk.back() == cnt){
                stk.pop_back();
                cnt++; i--;
            } else if (stk.back() > a[i]){
                stk.push_back(a[i]);
            } else {
                flag = false; break;
            }
        }
        string res = flag? "yes\n": "no\n";
        cout << res;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
