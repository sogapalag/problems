#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// time reversal, min-3 is last merge/divide group
//   i.e. 3it huffman coding
void solve() {
    int n; cin >> n;
    priority_queue<int, vector<int>, greater<int>> hp;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        hp.push(x);
    }
    if (n%2==0)hp.push(0);

    ll res = 0;
    while (hp.size() > 1) {
        assert(hp.size()>=3);
        int x = hp.top(); hp.pop();
        int y = hp.top(); hp.pop();
        int z = hp.top(); hp.pop();
        res += x+y+z;
        hp.push(x+y+z);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
