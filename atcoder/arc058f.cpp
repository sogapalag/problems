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

const char L = 'a'-1;
const char H = 'z'+1; 
const int N = 2001; 
const int LEN = 10001; 
bool dp[N][LEN];

// suppose we has min lexi string: mi.
// when new s[i] come, we wanna substitue part of it
// i.e. mi[..j] + s[i].
// so we need info whether we can append at j. after j+i, future could fix to T?
// and substitute should make lexi lower, or= but large length, since those info is useful
// among those substitute, choose best subs. (i.e. the first less-char idx is lower. note idx should be based on after subs.
void solve() {
    int n, T;
    cin >> n >> T;
    vector<string> s(n);
    for (auto& x: s) {
        cin >> x;
    }

    // prep dp
    dp[n][0] = true;
    for (int i = n-1; i >= 0; i--) {
        int len = s[i].size();
        memcpy(dp[i], dp[i+1], sizeof dp[i]);
        for (int j = 0; j <= T; j++) {
            if (j - len >= 0)
                dp[i][j] |= dp[i+1][j-len];
        }
    }

    // sustitute
    vector<bool> cat(T+1, false);
    cat[0] = true;
    string mi(T, H);
    for (int i = 0; i < n; i++) {
        string tmp = s[i] + L + mi;
        auto z = z_fn(tmp);
        int len = s[i].size();
        int id = -1;
        int min_len = T<<1;
        // pretest is weak
        // if use find smallest j, and don't set cat[j+lcp]. you can get AC.
        // but cannot pass
        //
        // 3 5
        // abcde
        // abc
        // cc
        //
        // which should output abccc
        // if you only change to set cat[j+lcp], then WA on abab0.txt test. since the algo is wrong choose smallest j.
        // we should choose min_len position to dec lexi
        // careful set cat, j downwards, otherwise use previous new_set
        for (int j = T-len; j >= 0; j--) {
            if (!cat[j] || !dp[i+1][T - (j+len)]) continue;
            int lcp = z[len+1+j];
            if (j + lcp >= T) continue;
            // 
            if (lcp == len) {
                cat[j+lcp] = true;
            }
            if (lcp >= len) continue;
            if (s[i][lcp] >= mi[j+lcp]) continue;
            if (j+lcp < min_len) {
                id = j;
                min_len = j+lcp;
            }
        }
        if (id == -1) continue;
        for (int j = 0; j < len; j++) {
            mi[id+j] = s[i][j];
        }
        for (int j = id+len; j < T; j++) {
            mi[j] = H;
        }
        for (int j = id+z[len+1+id]+1; j < T; j++) {
            cat[j] = false;
        }
        cat[id+len] = true;
    }
    
    cout << mi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
