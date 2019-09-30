#include <bits/stdc++.h>

using namespace std;


// note AA must Y, AB must N
// aka, Y cannot be AB, N cannot be AA
//
// so ignore N,~AA pair, remain at least one A. since A > B
// then note stk maintain a Y-> chain.
// back must be A, since if B, then by Y cannot be AB, thus all must B, contradiction. QED
void solve() {
    int A,B;
    cin >> A >> B;
    if (A<=B) { // |A| of B pretend to be A
        cout << "Impossible";
        return;
    }

    auto q = [](int x, int y)->bool{
        cout << "? " << x << ' ' << y << endl;
        string s; cin >> s;
        return s[0] == 'Y';
    };

    vector<int> stk;
    int n = A+B;
    for (int i = 0; i < n; i++) {
        if (stk.empty()) stk.emplace_back(i);
        else if (q(stk.back(), i)) stk.emplace_back(i);
        else stk.pop_back();
    }
    string res(n, '#');
    res[stk.back()] = '1';
    for (int i = 0; i < n; i++) {
        if (i==stk.back()) continue;
        res[i] = q(stk.back(), i)?'1':'0';
    }
    cout << "! " << res << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
