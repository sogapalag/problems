#include <bits/stdc++.h>

using namespace std;


// 00x => 000 => 00..0
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    bool occur = false;
    for (auto& x: a) {
        cin >> x;
        x = x>m ? 1 : (x < m ? -1 : 0);
        if (x==0) occur=true;
    }
    if (!occur) {
        cout << "no\n"; return;
    }
    if (n==1) {
        cout << "yes\n"; return;
    }
    int las = -3;
    // note 11x => 111 => 11..1, so create some 10 eventually
    //   10 => 00 => 00..0
    // so conclude below
    for (int i = 0; i < n; i++) {
        if (a[i]>=0) {
            if (i-las <= 2) {
                cout << "yes\n"; return;
            }
            las = i;
        }
    }
    cout << "no\n";
    /*
    auto ck = [&](){
        for (int i = 0; i < n; i++) {
            if (a[i]==0) {
                int j = i+1;
                int sum = 0;
                for (;j<n;j++) {
                    //sum += a[j];
                    a[j]<0 ? sum-- : sum++;
                    if (sum >= 0) return true;
                    if (a[j]==0) break;
                }
            }
        }
        return false;
    };
    if (n==1 && a[0]==0) {
        cout << "yes\n"; return;
    }
    if (ck()) {
        cout << "yes\n"; return;
    }
    reverse(a.begin(), a.end());
    if (ck()) {
        cout << "yes\n"; return;
    }
    cout << "no\n";
    */
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
