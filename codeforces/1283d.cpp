#include <bits/stdc++.h>

using namespace std;
using ll=long long;
struct Node {
    int d, len, x;
    Node() {}
    Node(int _d, int _len, int _x) : d(_d), len(_len), x(_x) {}
    bool operator<(const Node& _oth) const {
        return d>_oth.d;
    }
};

void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    priority_queue<Node> pq;
    const int NOTOVERFLOW = 1e9 + 1e6; 
    for (int i = 0; i < n; i++) {
        int l = i>0?a[i-1]:-NOTOVERFLOW;
        int x = a[i];
        int r = i<n-1?a[i+1]:NOTOVERFLOW;
        if (r-x>1) {
            int len = (r-x)/2;
            pq.push({1,len,x});
        }
        if (x-l>2) {
            int len = -((x-l-1)/2);
            pq.push({1,len,x});
        }
    }
    ll sum = 0;
    vector<int> res(m);
    for (int i = 0; i < m; i++) {
        auto t = pq.top(); pq.pop();
        sum += t.d;
        res[i] = t.x + (t.d * (t.len>0?1:-1));
        t.len > 0? t.len-- : t.len++;
        t.d++;
        if (t.len!=0) {
            pq.push(t);
        }
    }
    cout << sum << "\n";
    for (int x: res) {
        cout << x <<' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
