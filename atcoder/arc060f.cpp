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

int min_period(const vector<int>& z) {
    int n = z.size();
    for (int i = 1; i <= n/2; i++) {
        if (n%i) continue;
        if (z[i] == n-i) return i;
    }
    return n;
}

// when period in 1<p<n we can always find split=2
// so preprocess pre,suf is good
// (k-1)*p <= z[p] implies pre[k*p]:s[0..kp) has period p 
void solve() {
    string s; cin >> s;
    auto z = z_fn(s);
    int n = s.size();
    int period = min_period(z);
    if (period == 1) {
        cout << n << "\n1"; return;
    }
    if (period == n) {
        cout << "1\n1"; return;
    }
    
    vector<bool> pre(n+1, true), suf(n+1, true);
    for (int p = 1; p < n; p++) {
        if (!pre[p]) continue;  // delete then O(n log n)
        for (int k = 2; (k-1)*p <= z[p]; k++) {
            pre[k*p] = false;
        }
    }
    reverse(s.begin(), s.end());
    auto y = z_fn(s);
    for (int p = 1; p < n; p++) {
        if (!suf[p]) continue;
        for (int k = 2; (k-1)*p <= y[p]; k++) {
            suf[k*p] = false;
        }
    }
    int cnt = 0;
    for (int i = 1; i < n; i++) {
        if (pre[i] && suf[n-i]) cnt++;
    }
    assert(cnt);
    cout << "2\n" << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
