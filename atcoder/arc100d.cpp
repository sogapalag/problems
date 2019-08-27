#include <bits/stdc++.h>

using namespace std;

using ll=long long ;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<ll> pre(n+1), suf(n+1);
    pre[0] = 0;
    for (int i = 0; i < n; i++) {
        pre[i+1] = pre[i] + a[i];
    }
    suf[0] = 0;
    for (int i = 0; i < n; i++) {
        suf[i+1] = suf[i] + a[n-1-i];
    }
    ll res = 1e15;
    auto upd = [&](int p,int i,int k,int j){
        ll tmp = max({pre[p], pre[i]-pre[p], suf[k], suf[j]-suf[k]}) - min({pre[p], pre[i]-pre[p], suf[k], suf[j]-suf[k]});
        res = min(res, tmp);
    };
    for (int i = 2; i <= n-2; i++) {
        int j = n-i;
        int p = lower_bound(pre.begin()+1, pre.begin()+i, pre[i]/2) - pre.begin();
        int k = lower_bound(suf.begin()+1, suf.begin()+j, suf[j]/2) - suf.begin();
        if (p == i) p--;
        if (k == j) k--;
        upd(p,i,k,j);
        if (p>1) upd(p-1,i,k,j);
        if (k>1) upd(p,i,k-1,j);
        if (p>1 && k>1) upd(p-1,i,k-1,j);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
