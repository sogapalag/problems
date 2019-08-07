#include <bits/stdc++.h>

using namespace std;


// all reach RL knot
void solve() {
    string s; cin >> s;
    int n = s.size();
    vector<int> rl(n, 0);
    rl[0] = 1;
    for (int i = 1; i < n; i++) {
        if (s[i] == 'R') {
            rl[i] = rl[i-1] + 1;
        }
    }
    rl[n-1] = 1;
    for (int i = n-2; i >= 0; i--) {
        if (s[i] == 'L') {
            rl[i] = rl[i+1] + 1 - (s[i+1] == 'R');
        }
    }
    for (int i = 0; i < n; i++) {
        if (s[i]=='R' && s[i+1]=='L') {
            int x = (rl[i]+1)/2 + rl[i+1]/2;
            int y = rl[i]/2 + (rl[i+1]+1)/2;
            cout << x << " " << y << " ";
            i++;
        } else {
            cout << "0 ";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
