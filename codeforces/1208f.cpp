#include <bits/stdc++.h>

using namespace std;

const int L = 21; 
const int N = 1<<L;

int a[N];
int jk[N][2]; // store 2 right-most index, cover the mask. i.e. (y&z) & msk == msk

// note cover implies >
// so upd by additional cover bit, process down, since which already upd by more coverd-bit.
void solve() {
    int n; cin >> n;
    memset(jk, -1, sizeof jk);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = x;
        jk[x][0] = jk[x][1];
        jk[x][1] = i;
    }
    // two unique right-most
    auto upd = [&](int msk, int cov){
        int res[2] = {max(jk[msk][0], jk[cov][0]), max(jk[msk][1], jk[cov][1])};
        if (jk[msk][1] != jk[cov][1])
            res[0] = max(res[0], min(jk[msk][1], jk[cov][1]));
        jk[msk][0] = res[0];
        jk[msk][1] = res[1];
    };
    for (int msk = N-1; msk >= 0; msk--) {
        for (int j = 0; j < L; j++) {
            int cov = msk ^ (1<<j);
            if (cov > msk) upd(msk, cov);
        }
    }
    int res = 0;
    for (int i = 0; i < n-2; i++) {
        int x = a[i];
        int yz = 0;
        for (int j = L-1; j >= 0; j--) {
            if (x & (1<<j)) continue;
            yz ^= 1<<j;
            if (jk[yz][0] <= i)
                yz ^= 1<<j;
        }
        res = max(res, x | yz);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
