#include <bits/stdc++.h>

using namespace std;
using ll=long long;

struct MidPoint {
    priority_queue<int> L;
    priority_queue<int,vector<int>,greater<int>> R;
    ll res = 0;

    void LtoR() {
        res += L.top(); R.push(L.top());
        res += L.top(); L.pop();
    }
    void RtoL() {
        res -= R.top(); L.push(R.top());
        res -= R.top(); R.pop();
    }
    void push(int x) {
        if (L.empty() || x >= L.top()) {
            R.push(x); res += x;
        } else {
            LtoR();
            L.push(x); res -= x;
        }
        while (L.size() < R.size()) {
            RtoL();
        }
    }
};

void solve() {
    int n,k;
    cin >> k >> n;
    vector<pair<int, int>> a;
    ll base = 0;
    for (int _ = 0; _ < n; _++) {
        char c0,c1;
        int x,y;
        cin >> c0 >> x >> c1 >> y;
        if (x > y) swap(x,y);
        if (c0==c1) base += y-x;
        else a.emplace_back(x,y), base++;
    }

    if (k == 1) {
        vector<int> b;
        for (auto& _: a) {
            b.push_back(_.first);
            b.push_back(_.second);
        }
        sort(b.begin(), b.end());
        int m = b.size()/2;
        ll res = 0;
        for (int i = 0; i < m; i++) {
            res -= b[i];
            res += b[m*2-i-1];
        }
        cout << base+res;
    } else {
        sort(a.begin(), a.end(), [&](auto& u, auto& v){
            return u.first+u.second < v.first+v.second;
        });
        n = a.size();
        // ...
        if (n == 0) {
            cout << base; return;
        }
        vector<ll> pref(n);
        {
            MidPoint mid;
            for (int i = 0; i < n; i++) {
                mid.push(a[i].first);
                mid.push(a[i].second);
                pref[i] = mid.res;
            }
        }
        vector<ll> suff(n + 1);
        {
            MidPoint mid;
            for (int i = n-1; i >= 0; i--) {
                mid.push(a[i].first);
                mid.push(a[i].second);
                suff[i] = mid.res;
            }
        }
        ll res = 1e18;
        for (int i = 0; i < n; i++) {
            res = min(res, pref[i] + suff[i+1]);
        }
        cout << base + res;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
