#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int N = 51;

long long bino[N][N];

void bino_table() {
    for (int i = 0; i < N; i++) {
        bino[i][0] = 1;
        bino[i][i] = 1;
    }
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < i; j++) {
            bino[i][j] = (bino[i-1][j-1] + bino[i-1][j]) ;
        }
    }
}


void solve() {
    bino_table();
    cout << fixed << setprecision(8);
    int n, A, B;
    cin >> n >> A >> B;
    vector<ll> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end(), greater<ll>());
    double sum = 0;
    for (int i = 0; i < A; i++) {
        sum += a[i];
    }
    sum /= A;
    if (A>=n || a[A]!=a[0]) {
        int need = 0;
        for (int i = 0; i < A; i++) {
            if (a[i]==a[A-1]) need++;
        }
        int tot = 0;
        for (int i = 0; i < n; i++) {
            if (a[i]==a[A-1]) tot++;
        }
        ll res = bino[tot][need];
        cout << sum << "\n" << res; 
    } else {
        int i = A;
        for (; i < n;i++) {
            if (a[i] != a[0]) break;
        }
        ll res = 0;
        B = min(i, B);
        for (int j = A; j <= B; j++) {
            res += bino[i][j];
        }
        cout << sum << "\n" << res;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
