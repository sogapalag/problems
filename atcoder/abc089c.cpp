#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    char c[5] = {'M','A','R','C','H'};
    int a[5] = {0,0,0,0,0};
    for (int _ = 0; _ < n; _++) {
        string s; cin >> s;
        for (int i = 0; i < 5; i++) {
            if (s[0] == c[i]) a[i]++;
        }
    }
    long long res=0;
#define rep(i) for(int i=0;i<5;i++)
    rep(i)rep(j)rep(k)if(i!=j&&i!=k&&j!=k) {
        res += 1ll*a[i]*a[j]*a[k];
    }
    res /= 6;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
