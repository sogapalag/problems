#include <bits/stdc++.h>

using namespace std;
using ll=long long ;

// pairty iff
void solve() {
    int n; cin >> n;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int k = max_element(a.begin()+1, a.end()) - a.begin();
    ll res;
    int l,r;
    if (a[k] <= 0) res=a[k],l=k,r=k;
    else {
        ll s1 = 0;
        int l1 = 0, r1 = 0;
        for (int i = 1; i <= n; i+=2) {
            if (!l1 && a[i] > 0) l1 = i;
            if (a[i] > 0) r1 = i;
            if (a[i] > 0) s1 += a[i];
        }
        ll s2 = 0;
        int l2 = 0, r2 = 0;
        for (int i = 2; i <= n; i+=2) {
            if (!l2 && a[i] > 0) l2 = i;
            if (a[i] > 0) r2 = i;
            if (a[i] > 0) s2 += a[i];
        }
        if (s1 > s2) res=s1, l=l1, r=r1;
        else res=s2, l=l2, r=r2; 
    }
    cout << res << "\n";
    vector<int> pos;
    for (int i = n; i > r; i--) {
        pos.emplace_back(i);
    }
    while (l != r) {
        if (a[r-2] > 0) {
            pos.emplace_back(r-1);
        } else {
            pos.emplace_back(r-2);
        }
        r = r-2;
    }
    for (int i = 1; i < l; i++) {
        pos.emplace_back(1);
    }
    cout << pos.size() << "\n";
    for (auto& x: pos) {
        cout << x << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
