#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    bool alleq = true;
    int adjeq = -1;
    for (int i = 0; i < n; i++) {
        alleq &= (a[i]==a[0]);
        if (a[i]==a[(i+1)%n]) adjeq = i;
    }
    int res = 3;
    if (alleq) {
        res = 1;
    } else if (n % 2 == 0 || adjeq != -1) {
        res = 2;
    }
    cout << res << '\n';
    if (res == 1) {
        for (int _ = 0; _ < n; _++) {
            cout << "1 ";
        }cout << '\n';
    } else if(res==2){
        if (n%2==0) {
            for (int i = 0; i < n; i++) {
                cout << (i&1)+1 << ' ';
            }cout << '\n';
        } else {
            int i = adjeq;
            vector<int> c(n,-1);
            c[i]=c[(i+1)%n] = 1;
            for (int j = (i+1)%n; (j+1)%n != i; (j+=1)%=n) {
                c[(j+1)%n] = c[j]^3;
            }
            for (auto& x: c) {
                cout << x << ' ';
            }cout << '\n';
        }
    } else {
        cout << "3 ";
        for (int i = 1; i < n; i++) {
            cout << (i&1)+1 << ' ';
        }cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
