#include <bits/stdc++.h>

using namespace std;


// p=10, 1p0, pp' fixed. else can set 0
// so backwards braket stk match
void solve() {
    string s; cin >> s;
    int n = s.size();
    int stk = 0;
    for (int i = n-1; i >= 0; i--) {
        if (s[i] == '0') stk++;
        else if (stk == 0) s[i] = '0';
        else stk--;
    }
    cout << s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
