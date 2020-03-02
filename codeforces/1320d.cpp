#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const ll R = 843823891, iR = 1040004855;
const ll M = 1637348371;
inline ll add(ll x, ll y) {
    return (x+y) %M;
}
inline ll sub(ll x, ll y) {
    return (x-y + M) %M;
}
inline ll mul(ll x, ll y) {
    return (x*y) %M;
}

const int N = 2e5+10; 
ll pw[N];
ll suff[2][N];
int cnt[N];
ll a[2] = {37, 42};

// first method, "11" can be removed
// second method, 11..1 as coord, differ parity pos zeros, hold, cannot cross each other,
//    then some sophisticated, segment-tree, hash.  during contest have this idea.. and think merge count..
// below elegant method. not 11..1 as coord, its orignal coord(i:1..n) pairty doesn't change either.
//    then view zeros as some binary string. which is the token. equal iff.
void solve() {
    pw[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = mul(pw[i-1], R);
    }

    int n; cin >> n;
    string s; cin >> s;
    for (int i = n-1; i >= 0; i--) {
        if (s[i]=='1') {
            suff[0][i] = suff[0][i+1];
            suff[1][i] = suff[1][i+1];
            cnt[i] = cnt[i+1];
        } else {
            suff[0][i] = add(mul(suff[0][i+1], R), a[i&1]);
            suff[1][i] = add(mul(suff[1][i+1], R), a[(i&1)^1]);
            cnt[i] = cnt[i+1] + 1;
        }
    }

    auto get_hash = [&](int l, int r){
        int b = l&1;
        return sub(suff[b][l],  mul(suff[b][r], pw[cnt[l] - cnt[r]]));
    };

    int q; cin >> q;
    while (q--) {
        int i,j,len;
        cin >> i >> j >> len;
        i--;j--;
        if (get_hash(i,i+len) == get_hash(j,j+len)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
