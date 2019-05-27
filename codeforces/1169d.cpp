#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s;
    cin >> s;
    int n = s.size();
    long long res = 0;
    for (int i = 0; i < n; i++) {
        bool flag = false;
        int j = i;
        while (j < n && !flag) {
            bool tmp = false;
            for (int x = i; x < j; x++) {
                for (int k = 1; k <= j-i; k++) {
                    if (x+2*k <= j) {
                        if (s[x] == s[x+k] && s[x] == s[x+2*k]) {
                            tmp = true;break;
                        }
                    }
                }
                if (tmp) break;
            }
            if (tmp) {
                flag = true; break;
            } else {
                j++;
            }
        }
        if (flag) {
            res += n-j;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
