#include <bits/stdc++.h>

using namespace std;


// stack the res. if crt char can make progress, pop
void solve() {
    string s; cin >> s;
    vector<int> rem(26, 0);
    for (auto& x: s) {
        rem[x-'a']++;
    }
    vector<int> need(26);
    for (int i = 0; i < 26; i++) {
        need[i] = rem[i]/2;
    }
    vector<int> used(26, 0);
    reverse(s.begin(), s.end());
    string res; res.reserve(10'004);
    for (auto& x: s) {
        int k = x - 'a';
        if (used[k] == need[k]) {
            rem[k]--; continue;
        }
        while (!res.empty()) {
            int j = res.back() - 'a';
            if (j > k && used[j]-1+rem[j] >= need[j]) {
                used[j]--;
                res.pop_back();
            }else break;
        }
        used[k]++; rem[k]--;
        res.push_back(x);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
