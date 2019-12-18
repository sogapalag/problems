#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// each milestone must passed, exceed would no effect, so cost max(0)
void solve() {
    int n; cin >> n;
    ll sum = 0;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
        sum += x;
    }
    vector<int> fre(n, 0);

    auto cost = [&](int u){
        return max(0, a[u]-fre[u]);
    };

    int q; cin >> q;
    map<pair<int,int>, int> mp;
    while (q--) {
        int s, t, u;
        cin >> s >> t >> u;
        s--;u--;
        auto it = mp.find({s,t});
        if (it != mp.end()) {
            int v = it->second;
            sum -= cost(v);
            fre[v]--;
            sum += cost(v);
            if (u==-1) {
                mp.erase(it);
            } else {
                sum -= cost(u);
                fre[u]++;
                sum += cost(u);
                it->second = u;
            }
        } else if (u!=-1) {
                sum -= cost(u);
                fre[u]++;
                sum += cost(u);
                mp[{s,t}] = u;
        }
        cout << sum << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
