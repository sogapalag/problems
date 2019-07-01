#include <bits/stdc++.h>

using namespace std;

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}

const int N = 2e5+10; 
int cnt[N][26];

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    for (int i = 0; i < 26; i++) {
        cnt[0][i] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 26; j++) {
            cnt[i+1][j] = cnt[i][j]; 
        }
        cnt[i+1][s[i] - 'a']++;
    }
    int q; cin >> q;
    while (q--) {
        string x; cin >> x;
        vector<int> a(26, 0);
        for (auto& c: x) {
            a[c-'a']++;
        }
        int res = bs_first<int>(1, n+1, [&](int i){
                for (int j = 0; j < 26; j++) {
                    if (a[j] > cnt[i][j]) return false;
                }
                return true;
                });
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
