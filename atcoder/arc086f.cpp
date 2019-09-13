#include <bits/stdc++.h>

using namespace std;

using ll=long long ;

const ll MOD = 1000000007;

void add(ll& r, const ll& x){
    (r += x) %= MOD;
}

// min_x ones(x), x:[l,r]
int minpop(ll l, ll r){
    if (l == 0) return 0;
    l--;
    ll res = 0;
    for (int j = 60; j >= 0; j--) {
        ll k = 1ll << j;
        if ((l&k) ^ (r&k)) {
            res |= k; break;
        } else {
            res |= (l&k);
        }
    }
    return __builtin_popcountll(res);
}

// (X-p_0)/2 - p_1)/2 -../... = (X - P)/2^k, where P = sum_{i:[0,k)} 2^i p_i
// so ops <=> 1. -P,    2. /2^k   3. -p_k
// so consider use A, k times, X -> [X-P]/2^k - p_k = Y, 
// let k = 2^k
// let c = a%k, only P<=c? matter, Y or Y-1
// dedup c, for each range, we get the diff pattern, use map store the possible range for b[0]
void solve() {
    int n; ll K;
    cin >> n >> K;
    vector<ll> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    n = a.size();

    map<vector<ll>, vector<pair<ll,int>>> mp;
    for (int j = 0; j <= 60; j++) {
        vector<ll> c(n);
        ll k = 1ll << j;
        for (int i = 0; i < n; i++) {
            c[i] = a[i] & (k-1);
        }
        sort(c.begin(), c.end());
        c.erase(unique(c.begin(), c.end()), c.end());
        ll l = 0;
        for (ll r: c) {
            int mi = minpop(l, r);
            if (mi + j > K || r > a[0]) continue;
            vector<ll> b(n);
            for (int i = 0; i < n; i++) {
                b[i] = (a[i]-r) >> j;
            }
            vector<ll> pat; // diff pattern
            for (int i = 1; i < n; i++) {
                pat.emplace_back(b[i]-b[i-1]);
            }
            // b[0]'s range
            ll L = max(0ll, b[0] - (K-mi-j)), R = b[0];
            mp[pat].emplace_back(L, 0);
            mp[pat].emplace_back(R+1, 1);
            l = r+1;
        }
    }

    ll res = 0;
    for (auto& kv: mp) {
        auto& v = kv.second;
        if (v.empty()) continue;
        sort(v.begin(), v.end());
        ll l = v[0].first;
        int stk = 0;
        for (auto& p: v) {
            if (p.second) stk--;
            else {
                stk++;
                if (stk == 1) {
                    l = p.first;
                }
            }
            if (stk == 0) {
                add(res, p.first-l);
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
