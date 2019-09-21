#include <bits/stdc++.h>

using namespace std;


//  cut : <26  | 26 | ... | 26 | 
void solve() {
    string s; cin >> s;
    int n = s.size();
    set<char> box;

    vector<int> cut;
    cut.emplace_back(n);
    for (int i = n-1; i >= 0; i--) {
        box.insert(s[i]);
        if (box.size() == 26) {
            box.clear();
            cut.emplace_back(i);
        }
    }
    box.clear();
    reverse(cut.begin(), cut.end());
    string res;
    int crt = 0;
    int m = cut.size();
    for (int i = 0; i < m; i++) {
        box.clear();
        for (int j = crt; j < cut[i]; j++) {
            box.insert(s[j]);
        }
        char ans = 0;
        for (int k = 0; k < 26; k++) {
            if (box.find('a'+k) == box.end()) {
                ans = 'a'+k;
                res.push_back(ans);
                break;
            }
        }
        assert(ans);
        crt = cut[i];
        while (crt < n && s[crt] != ans) {
            crt++;
        }
        crt++;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
