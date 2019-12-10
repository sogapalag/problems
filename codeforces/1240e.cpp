#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const int N = 5e5+10; 

using pi = pair<int, int> ;
void upd(pi& p, int x) {
    p = {max(p.first, x), max(p.second, min(p.first, x))};
}

// for fixed y, x should take advantage best mod%y
void solve() {
    int n; cin >> n;
    vector<int> cnt(N);
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        cnt[x]++;
    }
    while (cnt.back() == 0) {
        cnt.pop_back();
    }
    int M = cnt.size() - 1;
    vector<int> sum(M+2), pre(M+2, -1);
    for (int i = 1; i <= M+1; i++) {
        sum[i] = sum[i-1] + cnt[i];
        pre[i] = cnt[i] ? i : pre[i-1];
    }
ll res = 4;
    for (int y = 2; y <= M; y++) {
        ll has = 0;
        int i;
        for (i = 1; i*y <= M; i++) {
            has += (ll)(sum[min(i*y+y-1, M+1)] - sum[i*y-1]) * i;
        }
        pi mx = {-1,-1};
        --i;
        int l = i*y, r = M+1;
        for (; i >= 0; --i, r = l, l -= y) {
            int best_pos = pre[r-1];
            if (best_pos >= l) {
                upd(mx, best_pos%y);
            }
            if (cnt[best_pos] == 1) best_pos = pre[best_pos-1];
            if (best_pos >= l) {
                upd(mx, best_pos%y);
            }

            // 2*x = i*y+mx0
            if (mx.first >= 0) {
                ll x = (i*y + mx.first) / 2;
                x = min(x, has - i);
                if(x>=2)res = max(res, x*y);
            }
            // x = i*y+mx1
            if (mx.second >= 0) {
                ll x = (i*y + mx.second);
                x = min(x, has - 2*i);
                if(x>=2)res = max(res, x*y);
            }
            // x = i*y+mx0, 
            if (mx.first >= 0) {
                ll x = (i*y + mx.first);
                if (sum[M+1] - sum[x-1] >= 2) {// ck #>=x >= 2
                    x = min(x, has - 2*i - 1); // one cost additional y
                    if(x>=2)res = max(res, x*y);
                }
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
