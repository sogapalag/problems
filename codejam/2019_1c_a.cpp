#include <bits/stdc++.h>

using namespace std;

const int N = 500;
char beat[256];
void solve() {
    int n; cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    auto get = [&](int i, int j){
        return s[i][j%s[i].size()];
    };
    vector<bool> del(n);
    string res;
    for (int j = 0; j < N; j++) {
        vector<int> got;
        for (int i = 0; i < n; i++) {
            if (!del[i]) {
                got.push_back(get(i,j));
            }
        }
        sort(got.begin(), got.end());
        got.erase(unique(got.begin(), got.end()), got.end());
        int m = got.size();
        if (m == 3) goto fail;
        else if (m == 2) {
            if (got[0] == 'R') {
                res.push_back('R');
            } else if (got[1] == 'R') {
                res.push_back('P');
            } else {
                res.push_back('S');
            }
        } else {
            if (got[0] == 'R') {
                res.push_back('P');
            } else if (got[0] == 'S') {
                res.push_back('R');
            } else {
                res.push_back('S');
            }
        }
        char c = beat[res.back()];
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (!del[i]) {
                if (get(i,j) == c) del[i]=1;
                else cnt++;
            }
        }
        if (cnt == 0) goto succ;
    }
fail:
    cout << "IMPOSSIBLE\n";
    return;
succ:
    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
beat['P'] = 'R';
beat['R'] = 'S';
beat['S'] = 'P';
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
