#include <bits/stdc++.h>

using namespace std;

const int NONE = 1e9; 
const int N = 100005; 
int n;
int a[N][2];
int len[N];

bool ck(int x[2], int y[2]) {
    return x[0]==y[0] || x[1]==y[1];
}

void divi(int l, int r) {
    if (r-l <= 1) return;
    int m = (l+r)/2;
    divi(l,m); divi(m,r);

    for (int p:{0,1}) {
        for (int dir:{0,1}) {
            int pivot[2] = {NONE, NONE};
            // use one of as pivot
            pivot[p] = a[m][p];
            int i=m,j=m;
            while (l <= i-1 && ck(pivot, a[i-1])) {
                --i;
            }
            while (j+1 < r && ck(pivot, a[j+1])) {
                ++j;
            }
            // choose another from left or right
            if (dir) {
                if (l <= i-1) pivot[p^1] = a[i-1][p^1];
            } else {
                if (j+1 < r)  pivot[p^1] = a[j+1][p^1];
            }
            // continue extend
            while (l <= i-1 && ck(pivot, a[i-1])) {
                --i;
            }
            while (j+1 < r && ck(pivot, a[j+1])) {
                ++j;
            }
            len[i] = max(len[i], j-i+1);
        }
    }
}
// one can see if use p0=i0, i is left, then p1=first k1
//  although this fit tow-pointer but hard to varify.
// key: instead fix left first, we fix mid first, p0=m0, 4 cases. d&c
//
// omit. another O(nlog^2n) method, note we can check (l..r, p0,p1) valid in O(log) (by IEP cnt=?len) if with some prep
//   thus for each l let p=l, bs r, then replace p{0/1}=r{0/1} bs again.(since the case first k must meet)
void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int d,x,y;
        cin >> d >> x >> y;
        a[i][0] = d+x;
        a[i][1] = d-y;
    }
    fill(len, len+n, 1);
    divi(0, n);
    int res = *max_element(len, len+n);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (len[i] == res) ++cnt;
    }
    cout << res << ' ' << cnt << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
