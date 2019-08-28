#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    int res = 0;
    auto f = [](int x){
        int e = 0;
        while (x%2==0) {
            x/=2;
            e++;
        }
        return e;
    };
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        res += f(x);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
