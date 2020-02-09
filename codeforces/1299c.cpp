#include <bits/stdc++.h>

using namespace std;
using ll=long long;
using pl=pair<ll,ll>;
#define sum first
#define cnt second
// it's easy to see we should pick min pref-avg to be a cut. but no idea to maintain, like segtree..
// it's geom.. if note lexi a <=> lexi p, might easier
// lower convex hull of (i,pref_sum)
void solve() {
    int n; cin >> n;
    vector<pl> avg;
    avg.emplace_back(0, 1);
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        avg.emplace_back(x, 1);
        while (avg.size() >= 2) {
            auto i = --avg.end();
            auto j = i; --j;
            if (j->sum * i->cnt < i->sum * j->cnt) break; // cannot merge
            j->sum += i->sum;
            j->cnt += i->cnt;
            avg.pop_back();
        }
    }
    cout << fixed << setprecision(10);
    for (auto& i: avg) if(i.sum){
        double x = (double)i.sum / i.cnt;
        for (int _ = 0; _ < i.cnt; _++) {
            cout << x << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
