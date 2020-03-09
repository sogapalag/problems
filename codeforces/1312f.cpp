#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int N = 2520;
const int M = 100; 
int sg[3][N + M];

// tail-period <= 10.
// so prep M+N, for large i fit in M...M+N
// a naive way prep 5^3 offline periods. or just set period as LCM=2520.
void solve() {
    memset(sg, 0, sizeof sg);
    int n,x,y,z;
    cin >> n >> x >> y >> z;
    for (int i = 1; i < N+M; i++) {
        {
            bool mex[4] = {};
            mex[sg[0][max(0,i-x)]] = 1;
            mex[sg[1][max(0,i-y)]] = 1;
            mex[sg[2][max(0,i-z)]] = 1;
            int k = 0;
            while (mex[k]) {
                k++;
            }
            sg[0][i] = k;
            //cerr<<k<<' ';
        }
        {
            bool mex[4] = {};
            mex[sg[0][max(0,i-x)]] = 1;
            mex[sg[2][max(0,i-z)]] = 1;
            int k = 0;
            while (mex[k]) {
                k++;
            }
            sg[1][i] = k;
            //cerr<<k<<' ';
        }
        {
            bool mex[4] = {};
            mex[sg[0][max(0,i-x)]] = 1;
            mex[sg[1][max(0,i-y)]] = 1;
            int k = 0;
            while (mex[k]) {
                k++;
            }
            sg[2][i] = k;
            //cerr<<k<<' ';
        }
        //cout << '\n';
    }

    auto get = [&](int x, ll i){
        if (i < N+M) return sg[x][i];
        return sg[x][M + (i-M)%N];
    };

    int sum = 0;
    vector<ll> a(n);
    for (auto& x: a) {
        cin >> x;
        sum ^= get(0, x);
    }
    if (sum == 0) {
        cout << "0\n";
    } else {
        int res = 0;
        for (ll len: a) {
            int tmp = sum ^ get(0, len);
            if ((tmp ^ get(0, max(len-x, 0ll))) == 0) res++;
            if ((tmp ^ get(1, max(len-y, 0ll))) == 0) res++;
            if ((tmp ^ get(2, max(len-z, 0ll))) == 0) res++;
        }
        cout << res << "\n";
    }
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
