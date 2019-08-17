#include <bits/stdc++.h>

using namespace std;

struct Node {
    int t, d;
    Node(){}
    Node(int _t, int _d) : t(_t), d(_d){}
    bool operator<(const Node& _r) const {
        return d > _r.d;
    }
};

// type t's first, once in, never out
void solve() {
    int n, k;
    cin >> n >> k;
    vector<Node> a(n);
    for (auto& p: a) {
        cin >> p.t >> p.d;
        p.t--;
    }
    sort(a.begin(), a.end());
    vector<bool> trk(n, false);
    vector<int> stk;
    int type = 0;
    long long sum = 0;
    for (int i = 0; i < k; i++) {
        int t = a[i].t, d = a[i].d;
        if (!trk[t]) {
            trk[t] = true; 
            type++;
        } else {
            stk.push_back(d);
        }
        sum += d;
    }
    long long res = sum + 1ll*type*type;
    for (int i = k; i < n; i++) {
        int t = a[i].t, d = a[i].d;
        if (stk.empty()) break;
        if (trk[t]) continue;
        trk[t] = true;
        type++;
        sum -= stk.back(); stk.pop_back();
        sum += d;
        res = max(res, sum + 1ll*type*type);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
