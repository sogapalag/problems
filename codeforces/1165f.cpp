#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+5; 
vector<int> d[N];
vector<int> dof[N];
void solve() {
	int n, m;
    cin >> n >> m;
    vector<int> k(n);
    for (auto& x: k) {
        cin >> x;
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        d[x-1].push_back(y-1);
        dof[y-1].push_back(x-1);
    }
    for (int i = 0; i < n; i++) {
        sort(dof[i].begin(), dof[i].end());
    }
    auto work = [&](int days){
        vector<int> need(k);
        int cash = 0;
        for (int i = 0; i < days; i++) {
            cash++;
            if (i >= N) continue;
            for (auto& t: d[i]) {
                // must pick the final latest day.
                // consider type 1 , 3, 1
                // if you buy 1, then you don't have enough money for 3.
                // since these is another 1. so always pick last to buy(choice)
                auto it = lower_bound(dof[t].begin(), dof[t].end(), days);
                it--;
                if (i != *it) continue;
                int buy = min(cash, need[t]);
                cash -= buy;
                need[t] -= buy;
            }
        }
        int rem = 0;
        for (auto& x: need) {
            rem += x;
        }
        return cash >= rem * 2;
    };
    int l = 0, r = N * 2;
    int mid;
    while (l != r) {
        mid = (l+r) / 2;
        if (work(mid)) {
            r = mid;
        }else{
            l = mid + 1;
        }
    }
    cout << r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
