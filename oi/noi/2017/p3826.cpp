#include <bits/stdc++.h>

using namespace std;
using ll=long long;

struct Reso {
    int x, i;
    Reso() {}
    Reso(int _x, int _i) : x(_x), i(_i) {}
    bool operator<(const Reso& _oth) const {
        return x < _oth.x;
    }
};
const int N = 1e5; 
// key: time-reversal. careful-impl
void solve() {
    int n,m,q;
    cin >> n >> m >> q;
    vector<int> price(n), special(n), cap(n), rate(n);
    vector<vector<Reso>> evs(N);
    for (int i = 0; i < n; i++) {
        cin >> price[i] >> special[i] >> cap[i] >> rate[i];
        if (!cap[i]) continue;
        --cap[i];
        evs[rate[i] ? min(N-1, cap[i]/rate[i]) : N-1].emplace_back(price[i]+special[i], -1);
        if (!cap[i]) continue;
        evs[rate[i] ? min(N-1, (cap[i]-1)/rate[i]) : N-1].emplace_back(price[i], i);
    }
    vector<int> used(n);
    priority_queue<Reso> pq;
    vector<int> a; // used
    ll sum = 0;
    // get res[N]
    for (int _ = N-1; _ >= 0; _--) {
        for (auto& z: evs[_]) pq.push(z);
        vector<int> considered;
        for (int k = 0; k < m && !pq.empty();) {
            auto [x,i] = pq.top(); pq.pop();
            if (i == -1) {
                sum += x; k++;
                a.push_back(x);
            } else {
                int could = min(m-k, cap[i]-_*rate[i] - used[i]); // how many i could use
                sum += could * 1ll * x; k += could; used[i] += could;
                while (could--) a.push_back(x);
                considered.push_back(i);
            }
        }
        for (int i: considered) if (used[i] < cap[i]){ // remain?
            pq.emplace(price[i], i);
        }
    }
    vector<ll> res(N+1);
    res[N] = sum;
    sort(a.begin(), a.end(), greater<int>());
    for (int _ = N-1; _ >= 1; _--) {
        // greedy use best, since larger day choices still less day choices
        while (a.size() > _*m) {
            sum -= a.back(); a.pop_back();
        }
        res[_] = sum;
    }
    while (q--) {
        int d; cin >> d;
        cout << res[d] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
