#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s, t, q;
    cin >> s >> t >> q;
    auto is_subseq = [&](){
        int n = s.size(), m = t.size();
        if (n > m) return false;
        int i = 0, j = 0;
        while (i < n) {
            while (j < m && t[j] != s[i]) {
                j++;
            }
            if (j >= m) return false;
            assert(s[i] == t[j]);
            i++; j++;
        }
        return true;
    };
    auto suf = [&](){
        vector<int> cnt(26, 0);
        for (auto& x: s) {
            cnt[x-'a']--;
        }
        for (auto& x: t) {
            cnt[x-'a']++;
        }
        vector<int> qc(26, 0);
        for (auto& x: q) {
            qc[x-'a']++;
        }
        for (int i = 0; i < 26; i++) {
            if (qc[i] < cnt[i]) return false;
        }
        return true;
    };
    bool res = is_subseq() && suf();
    cout << (res?"YES":"NO") << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--)solve();
    cout << endl;
}
