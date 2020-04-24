#include <bits/stdc++.h>

using namespace std;

vector<int> D = {0b1110111, 0b0010010, 0b1011101, 0b1011011, 0b0111010, 0b1101011, 0b1101111, 0b1010010, 0b1111111, 0b1111011};

const int N = 2048; 
bitset<N> dp[N];
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x: a) {
        string s; cin >> s;
        reverse(s.begin(), s.end());
        for (int i = 0; i < 7; i++) {
            x |= (s[i]-'0')<<i;
        }
    }
    reverse(a.begin(), a.end());
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        int x = a[i];
        for (int d: D) if((d&x) == x) {
            dp[i+1] |= dp[i]<<(__builtin_popcount(x^d));
        }
    }
    if (!dp[n][m]) {
        cout << -1; return;
    }
    string res(n,'?');
    int k = m;
    for (int i = n-1; i >= 0; i--) {
        int x = a[i];
        for (int z = 9; z >= 0; z--) {
            int d = D[z];
            if ((d&x) == x) {
                int c = __builtin_popcount(x^d);
                if (k>=c && dp[i][k-c]) {
                    k -= c;
                    res[i] = char('0'+z);
                    break;
                }
            }
        }
    }
    reverse(res.begin(), res.end());
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
