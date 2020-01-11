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

const int N = 2e5+10; 
const int L = 30; 
bool ok[N][L];
void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (auto& x: a) {
        cin >> x;
    }
    for (auto& x: b) {
        cin >> x;
    }
    for (int i = 0; i < L; i++) {
        for (int _ = 0; _ < 2; _++) {
            string s; s.reserve(3*n);
            for (int x:b) s.push_back((x>>i&1) ^ _);
            for (int x:a) s.push_back(x>>i&1);
            for (int x:a) s.push_back(x>>i&1);
            auto z = z_fn(s);
            // a[->] = b
            for (int k = 0; k < n; k++) {
                if (z[n+k] >= n) ok[k][i] |= true;
            }
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < L; i++) {
            if (!ok[k][i]) goto fail;
        }
        cout << k << ' ' << (a[k]^b[0]) << "\n";
fail:;;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
