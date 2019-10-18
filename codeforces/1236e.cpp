#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// for fixed x, y is continous-seg.
// so we wanna know left/right boarder of each x, greedy
// e.g. for L. 
//   we maintain cnt of y. then all element move down 1 step, except y=0, y=a[i]+1.
//   so we make the two up 1 step, coordinate +1
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(m);
    for (auto& x: a) {
        cin >> x;
        x--;
    }
    if (n == 1) {
        cout << 0; return;
    }
    vector<int> L(n+m+1), R(n+m+1);
    {
        int l = 0, r = n;
        for (int i = l; i < r; i++) {
            L[i] = 1;
        }
        for (int i = 0; i < m; i++) {
            int x = a[i];
            if (x < n-1) { // this method we don't need min/max boundary. coord-shift got it
                L[l+x+2] += L[l+x+1];
                L[l+x+1] = 0;
            }
            L[l+1] += L[l];
            L[l] = 0;
            l++;r++;
        }
        L[l+1] += L[l];
        L[l] = 0;
        l++; r++;
    }
    {
        int l = m+1, r = n+m+1;
        for (int i = l; i < r; i++) {
            R[i] = 1;
        }
        for (int i = 0; i < m; i++) {
            int x = a[i];
            if (x-1 >= 0) {
                R[l+x-2] += R[l+x-1];
                R[l+x-1] = 0;
            }
            R[l+n-2] += R[l+n-1];
            R[l+n-1] = 0;
            l--;r--;
        }
        R[l+n-2] += R[l+n-1];
        R[l+n-1] = 0;
        l--;r--;
    }
    ll res = 0;
    for (int j = 0; j < n; j++) {
        res -= 1ll*L[m+1+j]*j;
        res += 1ll*R[j]*(j+1);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
