#include <bits/stdc++.h>

using namespace std;

char s[3333];
void solve() {
    int n,k;
    cin >> n >> k;
    cin >> &s[1];
    s[0] = 'L'; s[n+1] = 'R';
    int lim = 0;
    for (int i = 1, r = 0; i <= n; i++) {
        if (s[i]=='L') lim += r;
        else r++;
    }
    if (k > lim) {
        cout << -1; return;
    }
    vector<vector<int>> g;
    auto fast = [&](){
        for (int i = n-1; i >= 1; i--) {
            if (s[i]=='R') {
                for (int j = i; j < n; j++) {
                    if (s[j+1] == 'L') {
                        g.push_back({j});
                        swap(s[j], s[j+1]);
                    } else break;
                }
            }
        }
    };
    while (lim) {
        if (lim == k) {
            fast(); break;
        }
        // don't need explict lower bound, since greedy will find it, ck k=0,lim>0
        vector<int> could;
        for (int i = 1; i < n; i++) {
            if (s[i]=='R' && s[i+1]=='L') could.push_back(i);
        }
        while (lim - could.size() < k-1) {
            could.pop_back();
        }
        for (int i:could) {
            swap(s[i], s[i+1]);
        }
        g.push_back(could);
        lim -= could.size();
        --k;
        if (k == 0 && lim > 0) {
            cout << -1; return;
        }
    }
    for (auto& a: g) {
        cout << a.size() << ' ';
        for (auto& x: a) {
            cout << x << ' ';
        }cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
