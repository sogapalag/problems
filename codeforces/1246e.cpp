#include <bits/stdc++.h>

using namespace std;

const int L = 16; 
const int N = 2008; 
bitset<N> dp[1<<L]; // dp[msk][sum] : sum = a_i * K^-b_i

void solve() {
    int n,K;
    cin >> n >> K;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    const int MSK = 1<<n; 
    dp[0][0] = 1;
    for (int msk = 1; msk < MSK; msk++) {
        for (int i = 0; i < n; i++) {
            if (msk & (1<<i)) {
                dp[msk] |= dp[msk^(1<<i)] << a[i];
            }
        }
        for (int i = N-1; i >= 1; i--) {
            if (dp[msk][i] && i%K == 0) {
                dp[msk][i/K] = 1;
            }
        }
    }

    if (!dp[MSK-1][1]) {
        cout << "NO"; return;
    }
    cout << "YES\n";
    int msk = MSK-1, cnt = 0, sum = 1;
    vector<int> b(n);
    while (msk) {
        while (sum*K < N && dp[msk][sum*K]) {
            sum *= K;
            cnt++;
        }
        for (int i = 0; i < n; i++) {
            if (msk & (1<<i)) {
                if (sum >= a[i] && dp[msk^(1<<i)][sum-a[i]]) {
                    b[i] = cnt;
                    sum -= a[i];
                    msk ^= 1<<i;
                    break; // without also AC
                }
            }
        }
    }
    priority_queue<pair<int,int>> pq;
    for (int i = 0; i < n; i++) {
        pq.push({b[i], a[i]});
    }
    while (pq.size() > 1) {
        int e,x;
        tie(e,x) = pq.top(); pq.pop();
        int f,y;
        tie(f,y) = pq.top(); pq.pop();
        assert(e == f);
        cout << x << ' ' << y << "\n";
        x += y;
        while (x % K == 0) {
            x /= K;
            e--;
        }
        pq.push({e,x});
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
