#include <bits/stdc++.h>

using namespace std;

void Y(){
    cout << "Yes\n";exit(0);
}
void N(){
    cout << "No\n";exit(0);
}

// for [l..=r] in a[l..=r], check(l,r)
// length odd
// l+1 +3,.. must a[i]=i else a[i]!=i
// and i<a[i], i>a[i] two groups both increasing
void solve() {
    int n; cin >> n;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    auto check = [&](int l, int r){
        if ((r-l)&1) N();
        for (int i = l+1; i < r; i+=2) {
            if (a[i] != i) N();
        }
        for (int i = l; i <= r; i+=2) {
            if (a[i] == i) N();
        }
        int x = 0, y = 0;
        for (int i = l; i <= r; i+=2) {
            if (a[i] < i) {
                if (a[i] < x) N();
                x = a[i];
            } else {
                if (a[i] < y) N();
                y = a[i];
            }
        }
    };
    int l = 1, r;
    while (true) {
        while (l <= n && a[l]==l) {
            l++;
        }
        if (l > n) Y();
        r = l;
        int mi = a[l], mx = a[l];
        while (r <= n && (l!=mi || r!=mx)) {
            r++;
            mi = min(mi, a[r]);
            mx = max(mx, a[r]);
        }
        check(l, r);
        l = r+1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
