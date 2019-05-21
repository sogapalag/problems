#include <bits/stdc++.h>

using namespace std;



void solve() {
    int n; cin >> n;
    string a; cin >> a;
    string b; cin >> b;
    unordered_set<string> sub[55];
    auto to_str = [](auto& v) -> string{
        string s(26, '0');
        for (int i = 0; i < 26; i++) {
            s[i] += v[i];
        }
        return s;
    };
    for (int d = 1; d <= n; d++) {
        for (int i = 0; i <= n-d; i++) {
            vector<int> cnt(26, 0);
            for (int j = i; j < i+d; j++) {
                cnt[b[j] - 'A']++;
            }
            sub[d].insert(to_str(cnt));
        }
    }
    int res = 0;
    for (int d = 1; d <= n; d++) {
        for (int i = 0; i <= n-d; i++) {
            vector<int> cnt(26, 0);
            for (int j = i; j < i+d; j++) {
                cnt[a[j] - 'A']++;
            }
            string s = to_str(cnt);
            if (sub[d].find(s) != sub[d].end()) res++;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
