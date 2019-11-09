#include <bits/stdc++.h>

using namespace std;

// imagine infinity grid, since under mod
// the pattern is
// 0, 1,... n-1
//           n ,n+1,....,2n-1
//                        0 , 1,...
//                                 ..
// thus let two group a=[0,n), b=[n,2n)
// for x, its lr-adj are same group -+1, ud-adj are differ group -+1
// and replace n+i to i, one can find still valid, just +-1, lr <-> ud
void solve() {
    int K; cin >> K;
    if (K == 1) {
        cout << "1\n1"; return;
    }
    int n = 2;
    while ((n&1) || K > 2*n ) {
        n++;
    }
    vector<int> a(n), b(n);
    iota(a.begin(), a.end(), 1);
    iota(b.begin(), b.end(), n+1);
    int cnt = 2*n - K;
    while (cnt > 0) {
        b[n-cnt] = a[n-cnt];
        cnt--;
    }
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int c = (i&1)? b[(i+j)%n] : a[(i+j)%n];
            cout << c << ' ';
        }cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
