#include <bits/stdc++.h>

using namespace std;

const int Z = 100005; 
const int N = 100005; 
bool ab[N+Z], ac[N+Z], bc[N+Z];

bool match(char c0, char c1){
    return (c0=='?'||c1=='?'||c0==c1);
}

// prep ab/ac/bc possible shift
// brute-force ab,ac shift, since which decide bc shift.
void solve() {
    string a,b,c;
    cin >> a >> b >> c;
    int A = a.size();
    int B = b.size();
    int C = c.size();
    int res = A+B+C;

    for (int i = 0; i < A; i++) {
        for (int j = 0; j < B; j++) {
            if (!match(a[i], b[j]))
                ab[i-j + Z] = 1;
        }
    }
    for (int i = 0; i < A; i++) {
        for (int j = 0; j < C; j++) {
            if (!match(a[i], c[j]))
                ac[i-j + Z] = 1;
        }
    }
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < C; j++) {
            if (!match(b[i], c[j]))
                bc[i-j + Z] = 1;
        }
    }
    const int M = 2020 * 2; 
    for (int i = -M; i < M; i++) {
        for (int j = -M; j < M; j++) {
            if (!ab[i+Z] && !ac[j+Z] && !bc[j-i+Z]) {
                int L = min({0,i,j});
                int R = max({A,i+B,j+C});
                res = min(res, R-L);
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
