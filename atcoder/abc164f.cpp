#include <bits/stdc++.h>

using namespace std;
using u64 = unsigned long long;
const int N = 512; 
u64 a[N][N];

void exitif(bool b) {
    if (b) {
        cout << -1 << endl; exit(0);
    }
}

// there're many method. hard part is careful-impl
void solve() {
    int n; cin >> n;
    vector<int> sr(n), sc(n);
    vector<u64> ar(n), ac(n);
    for (auto& x: sr) cin >> x;
    for (auto& x: sc) cin >> x;
    for (auto& x: ar) cin >> x;
    for (auto& x: ac) cin >> x;
    if (n == 1) {
        exitif(ar[0] != ac[0]);
        cout << ar[0]; return;
    }

    for (int k = 0; k < 64; k++) {
        vector<int> AR[2], AC[2];
        vector<int> ER[2], EC[2];
        for (int i = 0; i < n; i++) {
            bool bit = ar[i]>>k&1;
            if (!sr[i]) {
                if (bit) AR[1].push_back(i);
                else ER[0].push_back(i);
            } else {
                if (bit) ER[1].push_back(i);
                else AR[0].push_back(i);
            }
        }
        for (int i = 0; i < n; i++) {
            bool bit = ac[i]>>k&1;
            if (!sc[i]) {
                if (bit) AC[1].push_back(i);
                else EC[0].push_back(i);
            } else {
                if (bit) EC[1].push_back(i);
                else AC[0].push_back(i);
            }
        }
        exitif(!AR[0].empty() && !AC[1].empty());
        exitif(!AR[1].empty() && !AC[0].empty());
        exitif(AR[0].size() == n && EC[1].size());
        exitif(AC[0].size() == n && ER[1].size());
        exitif(AR[1].size() == n && EC[0].size());
        exitif(AC[1].size() == n && ER[0].size());
        // + shape
        if (AR[0].size()+AR[1].size() > 0 && AC[0].size()+AC[1].size() > 0) {
            u64 b = !AR[1].empty();
            vector<bool> tr(n), tc(n);
            for (int i:AR[b]) tr[i] = 1;
            for (int j:AC[b]) tc[j] = 1;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    u64 x = tr[i] || tc[j];
                    a[i][j] |= (b ^ x ^ 1) << k;
                }
            }
        // - shape
        } else {
            bool swaped = false;
            if (AC[0].size()+AC[1].size() > 0) {
                swaped = true;
                swap(AC[0], AR[0]);
                swap(AC[1], AR[1]);
                swap(EC[0], ER[0]);
                swap(EC[1], ER[1]);
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < i; j++) {
                        swap(a[i][j], a[j][i]);
                    }
                }
            }
            // a[i][i]=b, result col[i] contradiction
            for (int b = 0; b < 2; b++) {
                exitif(AR[b].size() + ER[b].size() == n && ER[b].size() == 1 && EC[b^1].size() == n);
            }
            vector<bool> tr(n), tc(n);
            // fill AR
            for (int i:AR[1]) {
                tr[i] = 1;
                for (int j = 0; j < n; j++) {
                    a[i][j] |= (u64(1))<<k;
                }
            }
            for (int i:AR[0]) tr[i]=1;
            // fill EC for non-AR
            for (int j:EC[1]) {
                for (int i = 0; i < n; i++) if(!tr[i]){
                    a[i][j] |= (u64(1))<<k;
                }
            }
            // only when empty a[i][i] change
            for (u64 b = 0; b < 2; b++) {
                for (int i:ER[b]) if (EC[b].empty()) {
                    a[i][i] ^= (u64(1))<<k;
                }
            }
            if (swaped) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < i; j++) {
                        swap(a[i][j], a[j][i]);
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << ' ';
        }cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
