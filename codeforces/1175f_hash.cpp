#include <bits/stdc++.h>

using namespace std;


using ll=long long ;
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int res = 0;
    int cnt = 0;
    mt19937_64 rnd(time(NULL));
    vector<ll> hsh(n+1);
    vector<ll> perm(n+1);
    perm[0] = 0;
    for (int i = 1; i <= n; i++) {
        hsh[i] = rnd();
        perm[i] = perm[i-1] ^ hsh[i];
    }
    vector<ll> sum(n+1); 
    auto is_perm = [&](int l, int r){
        int t = r-l+1;
        return (sum[r+1] ^ sum[l]) == perm[t];
    };
    auto calc = [&](int i){
        int r = i+1, len = 1;
        while (r < n && a[r] != 1) {
            len = max(len, a[r]);
            int l = r - len + 1;
            if (l >= 0 && is_perm(l, r))
                res++;
            r++;
        }
    };
    auto doo = [&](){
        sum[0] = 0;
        for (int i = 0; i < n; i++) {
            sum[i+1] = sum[i] ^ hsh[a[i]];
        }
        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                cnt++;
                calc(i);
            }
        }
    };
    doo();
    res += cnt;
    reverse(a.begin(), a.end());
    doo();
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
