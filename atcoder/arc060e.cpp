#include <bits/stdc++.h>

using namespace std;

const int N = 100005; 
const int L = 18; 
int toR[L][N];
int toL[L][N];

// toL is overkill.. a->b b->a exact greedy may differ, but since each method could reverse follow. so optim same
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int D; cin >> D;
    for (int i = 0; i < n; i++) {
        int j = upper_bound(a.begin(), a.end(), a[i]+D) - a.begin();
        toR[0][i] = j - 1;
    }
    for (int j = 1; j < L; j++) {
        for (int i = 0; i < n; i++) {
            toR[j][i] = toR[j-1][toR[j-1][i]];
        }
    }
    for (int i = 0; i < n; i++) {
        int j = lower_bound(a.begin(), a.end(), a[i]-D) - a.begin();
        toL[0][i] = j;
    }
    for (int j = 1; j < L; j++) {
        for (int i = 0; i < n; i++) {
            toL[j][i] = toL[j-1][toL[j-1][i]];
        }
    }
    int q; cin >> q;
    while (q--) {
        int i,k;
        cin >> i >> k;
        i--; k--;
        if (i < k) {
            int res = 0;
            for (int j = L-1; j >= 0; j--) {
                if (toR[j][i] >= k) continue;
                res |= 1<<j;
                i = toR[j][i];
            }if (i<k) res++;
            cout << res << "\n";
        } else {
            int res = 0;
            for (int j = L-1; j >= 0; j--) {
                if (toL[j][i] <= k) continue;
                res |= 1<<j;
                i = toL[j][i];
            }if (i>k) res++;
            cout << res << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
