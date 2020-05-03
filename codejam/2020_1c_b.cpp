#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int N = 1e4; 
// https://en.wikipedia.org/wiki/Benford%27s_law
// leading digit
void solve() {
    int L; cin >> L;
    vector<bool> leading(26);
    vector<int> cnt(26);
    vector<bool> occur(26);
    for (int _ = 0; _ < N; _++) {
        ll m; string s; // ll
        cin >> m >> s;
        leading[s[0]-'A'] = true;
        cnt[s[0]-'A']++;
        for (char c:s) occur[c-'A']=true;
        //for (char c:s) cnt[c-'A']++;
    }
    string res(10, '?');
    vector<int> a;
    for (int i = 0; i < 26; i++) {
        if (occur[i]) {
            if (!leading[i]) res[0] = char('A'+i);
            else a.push_back(i);
        }
    }
    sort(a.begin(), a.end(), [&](auto& u, auto& v){
        return cnt[u] > cnt[v];
    });
    for (int i = 1; i <= 9; i++) {
        res[i] = char('A' + a[i-1]);
    }
    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
