#include <bits/stdc++.h>

using namespace std;
using pi=pair<int, int> ;
using ll=long long;
void __solve() {
    int n; cin >> n;
    priority_queue<pi, vector<pi>, greater<pi>> hp;
    ll arbitrage = 0;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        if (!hp.empty() && hp.top().first < x) {
            int price, pre;
            tie(price, pre) = hp.top(); hp.pop();
            arbitrage += x - price;
            if (pre != -1) hp.emplace(price, -1), hp.emplace(x, pre);
            else hp.emplace(x, price);
        } else {
            hp.emplace(x, -1);
        }
    }
    cout << arbitrage;
}

// whenever we can arbitrage, we do.
void solve() {
    int n; cin >> n;
    priority_queue<int, vector<int>, greater<int>> hp;
    ll arbitrage = 0;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        if (!hp.empty() && hp.top() < x) {
            arbitrage += x - hp.top(); hp.pop();
            hp.push(x); // meaning, any can replace it sell
        }
        hp.push(x); // we can assume, always consume above be replaced first, thus also an option produce.
        // another easy to understand, hp store x that with -, for future pair up some +
        // so above pair-up, (+ | -,-) => (-)  since as long as one pos's #- <=1 is valid.
    }
    cout << arbitrage;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
