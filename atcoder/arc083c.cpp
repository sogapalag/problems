#include <bits/stdc++.h>

using namespace std;

const int N = 3010; 
bool wat[N], sug[N];
void solve() {
    int a,b,c,d,e,f;
    cin >> a >> b >> c >> d >> e >> f;
    a*=100; b*=100;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N && j*a<=i; j++) {
            if ((i-j*a)%b == 0) wat[i] = true;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N && j*c<=i; j++) {
            if ((i-j*c)%d == 0) sug[i] = true;
        }
    }
    int x=0,y=1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i+j > f) break;
            if (!sug[i] || !wat[j]) continue;
            if (i*100 > e*j) continue;
            if (i*y >= x*j) {
                x = i;
                y = j;
            }
        }
    }
    cout << (x+y) << ' ' << x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
