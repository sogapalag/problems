#include <bits/stdc++.h>

using namespace std;
using ll=long long;
using pi = pair<ll,int>;

void solve() {
    int n; cin >> n;
    vector<int> ord(n);
    ord[0] = 0, ord[n-1] = 4*n;
    priority_queue<pi> pq[2];
    for (int i = 1; i < n-1; i++) {
        cout << "1 1 " << (n) << ' ' << (i+1) << endl;
        ll S; cin >> S;
        cout << "2 1 " << (n) << ' ' << (i+1) << endl;
        int x; cin >> x;
        pq[x==1].push({S, i});
    }

    if(!pq[0].empty()){
        int l = 2*n, r = 2*n+1;
        int u = pq[0].top().second; pq[0].pop();
        ord[u] = l--;
        while (!pq[0].empty()) {
            int i = pq[0].top().second; pq[0].pop();
            cout << "2 1 " << u+1 << ' ' << (i+1) << endl;
            int x; cin >> x;
            if (x == 1) {
                ord[i] = r++;
            } else {
                ord[i] = l--;
            }
        }
    }

    if (!pq[1].empty()) {
        int l = 7*n, r = 7*n+1;
        int u = pq[1].top().second; pq[1].pop();
        ord[u] = r++;
        while (!pq[1].empty()) {
            int i = pq[1].top().second; pq[1].pop();
            cout << "2 1 " << u+1 << ' ' << (i+1) << endl;
            int x; cin >> x;
            if (x == 1) {
                ord[i] = r++;
            } else {
                ord[i] = l--;
            }
        }
    }
    //cout << "0 ";
    //for (auto& x: ord) {
    //    cout << x << ' ';
    //}cout << endl;
    
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return ord[u] < ord[v];
    });
    cout << "0 ";
    for (auto& x: id) {
        cout << (x+1) << ' ';
    }cout << endl;
    //vector<int> res(n);
    //for (int i = 0; i < n; i++) {
    //    res[id[i]] = i+1;
    //}
    //cout << "0 ";
    //for (auto& x: res) {
    //    cout << x << ' ';
    //}cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
