#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int N = 19; 
ll fac[N];
int n,K; ll S;
vector<ll> a;

map<ll,int> cnt[13];

void dfs(int i, ll sum, int stik=0) {
    if (sum > S) return;
    if (i == n/2) {
        cnt[stik][sum]++;return;
    }
    dfs(i+1, sum+a[i], stik);
    dfs(i+1, sum, stik); //skip
    if (a[i] < N && stik < K) dfs(i+1, sum + fac[a[i]], stik+1);
}

ll res = 0;
void match(int i, ll sum, int stik=0) {
    if (sum > S) return;
    if (i == n) {
        int k = min(K - stik, 12);
        res += cnt[k][S-sum];
        return;
    }
    match(i+1, sum+a[i], stik);
    match(i+1, sum, stik); //skip
    if (a[i] < N && stik < K) match(i+1, sum + fac[a[i]], stik+1);
}

void solve() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i-1]*i;
    }
    cin >> n >> K >> S;
    a.resize(n);
    for (auto& x: a) {
        cin >> x;
    }

    dfs(0, 0);
    // pref
    for (int i = 1; i < 13; i++) {
        for (auto& _: cnt[i-1]) {
            cnt[i][_.first] += _.second;
        }
    }
    match(n/2,0);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
