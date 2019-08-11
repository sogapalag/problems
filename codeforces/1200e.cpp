#include <bits/stdc++.h>

using namespace std;

using ll=long long;
void solve() {
    const long long R = 843823891;
    const long long M = 1637348371;
    vector<long long> pw(1000'006);
    pw[0] = 1;
    for (int i = 1; i < (int)pw.size(); i++) {
        pw[i] = (pw[i-1] * R) % M;
    }

    int q; cin >> q;
    string res = ""; res.reserve(1000'006);
    vector<ll> hsh(1000'006);

    for (int _ = 0; _ < q; _++) {
        string s; cin >> s;
        int n = s.size();
        vector<ll> sum(n+1);
        sum[0] = 0;
        for (int i = 0; i < n; i++) {
            sum[i+1] = (sum[i] + pw[i]*(s[i]-'0'+42)%M) % M;// -'a' may negtive
        }
        int m = res.size();
        for (int i = min(n, m); i >= 0; i--) {
            if (sum[i]*pw[m-i]%M == (hsh[m]-hsh[m-i]+M)%M) {
                for (int j = i; j < n; j++) {
                    res += s[j];
                    hsh[m+j-i+1] = (hsh[m+j-i] + pw[m+j-i]*(s[j]-'0'+42)%M) %M;
                }
                break;
            }
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
