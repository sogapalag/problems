#include <bits/stdc++.h>

using namespace std;


void solve() {
    int A, B;
    cin >> A >> B;
    int N = A+B;
    auto f = [&](int d){
        int l = N/(d+1) + 1, r = N/d;
        int a[2] = {(A+d)/(d+1), A/d};
        int b[2] = {(B+d)/(d+1), B/d};
        if (l <= r && a[0] <= a[1] && b[0] <= b[1]) {
            l = max(l, a[0]+b[0]);
            r = min(r, a[1]+b[1]);
            if (l <= r)
                return r-l+1;
        }
        return 0;
    };
    int res = 0;
    for (int i = 1; i <= N;) {
        int d = N/i;
        res += f(d);
        i = N/d + 1;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
