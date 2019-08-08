#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START rabin_karp
// text/pattern, ret: match start pos(0-based). method rolling hash
vector<int> rabin_karp(const string& t, const string& p) {
    const long long R = 843823891;
    const long long M = 1637348371;
    int n = t.size(), m = p.size();
    vector<long long> pw(max(n,m));
    pw[0] = 1;
    for (int i = 1; i < (int)pw.size(); i++) {
        pw[i] = (pw[i-1] * R) % M;
    }

    // sum[i+1] = \sum_[0..=i] t_i * R^i
    vector<long long> sum(n+1);
    sum[0] = 0;
    for (int i = 0; i < n; i++) {
        sum[i+1] = (sum[i] + pw[i]*(t[i]-'a'+42)%M) % M;
    }
    long long hsh = 0;
    for (int i = 0; i < m; i++) {
        hsh = (hsh + pw[i]*(p[i]-'a'+42)%M) % M;
    }
    vector<int> pos;
    for (int i = 0; i+m <= n; i++) {
        if (hsh*pw[i]%M == (sum[i+m]-sum[i]+M)%M)
            pos.push_back(i);
    }
    return pos;
}
// SNIPPETS_END
