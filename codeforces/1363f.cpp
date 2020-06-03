#include <bits/stdc++.h>

using namespace std;

void mini(int& x, int y) {
    if (x > y) x = y;
}

const int N = 2048; 
const int INF = 1e9; 
using Freq=array<int,26>;
int dp[N][N];

// trick part is understand dp meaning.
// and note #op = #inseert
void solve() {
    int n; cin >> n;
    string s,t;
    cin >> s >> t;
    swap(s,t); // problem =>(dual) take char from s insert after
    {
        Freq f = {};
        for (int i = 0; i < n; i++) {
            f[s[i]-'a']++;
            f[t[i]-'a']--;
        }
        for (int i = 0; i < 26; i++) {
            if (f[i] != 0) {
                cout << "-1\n"; return;
            }
        }
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = INF;
        }
    }
    // dp[i][j] := min op needed to make s[0..i) = t[0..j), in sense with i-j(from s into g) still unused. i>=j
    dp[0][0] = 0;
    Freq f = {};
    for (int i = 0; i <= n; i++) {
        auto g = f; // resource
        for (int j = 0; j <= i && j < n; j++) {
            // use one insert
            if (g[t[j]-'a'] > 0) mini(dp[i][j+1], dp[i][j]);
            // match
            if (s[i]==t[j]) mini(dp[i+1][j+1], dp[i][j]);
            // reserve for future inesrt
            mini(dp[i+1][j], dp[i][j] + 1);
            if (--g[t[j]-'a'] < 0) break;
        }
        if (i != n) f[s[i]-'a']++;
    }
    cout << dp[n][n] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
