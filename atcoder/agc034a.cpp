#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,A,B,C,D;
    cin >> n >> A >> B >> C >> D;
    A--;B--;C--;D--;
    string s; cin >> s;
    auto ck = [&](int x, int y){
        for (int i = x; i < y; i++) {
            if (s[i]=='#' && s[i+1]=='#') return false;
        }
        return true;
    };
    if (ck(A,C) && ck(B,D)) {
        if (C < D) {
            cout << "Yes";
        } else {
            bool across = false;
            for (int i = B; i <= D; i++) {
                if (s[i]=='.' && s[i-1]=='.' && s[i+1]=='.') {
                    across = true; break;
                }
            }
            cout << (across?"Yes":"No");
        }
    } else {
        cout << "No";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
