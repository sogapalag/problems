#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const long long INF = 0x3f3f3f3f3f3f3f3f;
const int N = 51; 
ll fib[N];
void prep() {
    fib[0] = 1; fib[1] = 1;
    for (int i = 2; i < N; i++) {
        fib[i] = fib[i-1] + fib[i-2];
        if (fib[i] > INF) fib[i] = INF;
    }
}
// similar to hard one 1279e.
// but the problem require perm(3 1 2), repre. 3->2->1, so impossible, each cycle |len|<3
void solve() {
    prep();
    int n; ll k;
    cin >> n >> k; k--;
    for (int i = 1; i <= n; i++) {
        int len = n - i;
        if (k < fib[len]) {
            cout << i << ' ';
        } else {
            k -= fib[len];
            cout << ++i << ' ';
            cout << i-1 << ' ';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
