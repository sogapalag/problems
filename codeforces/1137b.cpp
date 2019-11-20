#include <bits/stdc++.h>

using namespace std;

// z[i] = len of lcp of s, s[i..]; lcp(longest common prefix)
vector<int> z_fn(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r)
            z[i] = min(r-i+1, z[i-l]);
        while (i+z[i] < n && s[z[i]] == s[i+z[i]]) {
            z[i]++;
        }
        if (i+z[i]-1 > r) {
            l = i; r = i+z[i]-1;
        }
    }
    return z;
}

void solve() {
    string s,t;
    cin >> s >> t;
    if (s.size() < t.size()) {
        cout << s; return;
    }
    int cnt[2] = {};
    for (char c:s)cnt[c-'0']++;
    auto z = z_fn(t);
    int n = z.size();
    int i = 1;
    for (;i<n;i++){
        if (z[i] == n-i) break;
    }

    string res;
    auto fill = [&](){
        while (cnt[0] > 0) {
            cnt[0]--;
            res += '0';
        }
        while (cnt[1] > 0) {
            cnt[1]--;
            res += '1';
        }
    };
    for (int k = 0; k < n-i; k++) {
        if (cnt[t[k]-'0'] > 0) {
            cnt[t[k]-'0']--;
            res += t[k];
        } else {
            fill(); break;
        }
    }
    while (res.size() < s.size()) {
        for (int k = n-i; k < n; k++) {
            if (cnt[t[k]-'0'] > 0) {
                cnt[t[k]-'0']--;
                res += t[k];
            } else {
                fill(); break;
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
