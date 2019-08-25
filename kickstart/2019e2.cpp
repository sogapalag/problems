#include <bits/stdc++.h>

using namespace std;

using ll=long long ;
struct Slot {
    int c,e;
    Slot() {}
    Slot(int _c, int _e): c(_c), e(_e) {}
    bool operator<(const Slot& _s)const {
        return (ll) e * _s.c < (ll)c * _s.e;// 10^4 * 10^4..not neccessary. cost pen..
    }
};

// sort by e/c. main pre(c), suf(e)
void solve() {
    int n, m;
    cin >> n >> m;
    vector<Slot> a(m);
    for (int i = 0; i < m; i++) {
        int x,y;
        cin >> x >> y;
        a[i] = {x,y};
    }
    sort(a.begin(), a.end());
    vector<int> C(m+1);
    C[0] = 0;
    for (int i = 0; i < m; i++) {
        C[i+1] = C[i] + a[i].c;
    }
    vector<int> E(m+1);
    E[m] = 0;
    for (int i = m; i >= 1; i--) {
        E[i-1] = E[i] + a[i-1].e;
    }
    for (int _ = 0; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        int i = lower_bound(C.begin(), C.end(), x) - C.begin();
        if (i > m) {
            cout << 'N'; continue;
        }
        if (i == 0) {
            char res = E[0]>=y ? 'Y' : 'N';
            cout << res; continue;
        }
        double k = double(a[i-1].e) / double(a[i-1].c);
        double mx = (double)E[i] + k * (C[i]-x);
        char res = mx >= (double)y ? 'Y' : 'N';
        cout << res;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
