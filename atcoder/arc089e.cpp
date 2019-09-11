#include <bits/stdc++.h>

using namespace std;

int d[13][13];
const int N = 100; 
int f[N+1][N+1];

void solve() {
    int A,B;
    cin >> A >> B;
    for (int i = 1; i <= A; i++) {
        for (int j = 1; j <= B; j++) {
            cin >> d[i][j];
        }
    }
    memset(f, 0, sizeof f);
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            for (int x = 1; x <= A; x++) {
                for (int y = 1; y <= B; y++) {
                    f[i][j] = max(f[i][j], d[x][y] - x*i - y*j);
                }
            }
        }
    }
    for (int x = 1; x <= A; x++) {
        for (int y = 1; y <= B; y++) {
            int mi =  1e5;
            for (int i = 0; i <= N; i++) {
                for (int j = 0; j <= N; j++) {
                    mi = min(mi, x*i+y*j + f[i][j]);
                }
            }
            if (mi != d[x][y]) {
                cout << "Impossible"; return;
            }
        }
    }
    // S->.X.->
    // ->.Y.->T
    vector<int> a(N+1), b(N+1);
    iota(a.begin(), a.end(), 1);
    iota(b.begin(), b.end(), 102);
    int s = a[0], t = b[0];
    int m = 100*2 + 101*101;
    cout << "Possible\n";
    cout << "202 " << m << "\n";
    for (int i = 1; i <= N; i++) {
        cout << a[i-1] << ' ' << a[i] << " X\n";
        cout << b[i] << ' ' << b[i-1] << " Y\n";
    }
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            cout << a[i] << ' ' << b[j] << ' ' << f[i][j] << "\n";
        }
    }
    cout << s << ' ' << t;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
