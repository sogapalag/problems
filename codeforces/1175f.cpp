#include <bits/stdc++.h>

using namespace std;


// there are multiple method, one should notice there're O(n) not O(n^2) valid can be perm.
// so we need brute force check but not every (l,r) pair.
// in calc, notice perm must has '1', so iter r from '1' until next '1', also note occur x implies len>=x
// thus we can do effective check, and reverse array do again.
// also note, we don't do dup. since a[l] \neq a[r], so for a valid perm, this ensure only count once
//
// then form check [l..r] is valid perm. we can
// 1. use hash
// or with a unique table, record uni[r]: left-most index [l..r] are distinct.
// 2. check sum =(len+1 \C 2)
// 3. check max =len, (since ensure no negative.)
using ll=long long ;
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int res = 0;
    int cnt = 0;
    vector<ll> sum(n+1);
    vector<int> uni(n);
    auto is_perm = [&](int l, int r){
        ll t = r-l+1;
        return l >= uni[r] && sum[r+1] - sum[l] == t*(t+1)/2;
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
            sum[i+1] = sum[i] + a[i];
        }
        vector<int> saw(n+1, -1);
        uni[0] = 0; saw[a[0]] = 0;
        for (int i = 1; i < n; i++) {
            uni[i] = max(uni[i-1],  saw[a[i]] + 1);
            saw[a[i]] = i;
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
