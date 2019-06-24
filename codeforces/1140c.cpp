#include <bits/stdc++.h>

using namespace std;

struct Node {
    int t, b;
    Node() {}
    Node(int _t, int _b) : t(_t), b(_b) {}
};
using ll=long long;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<Node> a(n);
    for (int i = 0; i < n; i++) {
        int t, b;
        cin >> t >> b;
        a[i] = {t, b};
    }
    sort(a.begin(), a.end(), [&](auto& u, auto& v){
            return u.b > v.b;
            });
    ll sum = 0;
    ll res = 0;
    multiset<int> st;
    for (int i = 0; i < n; i++) {
        if (i < k) {
            sum += a[i].t;
            st.insert(a[i].t);
        } else {
            if (a[i].t > *st.begin()) {
                sum += a[i].t - *st.begin();
                st.erase(st.begin());
                st.insert(a[i].t);
            }
        }
        res = max(res, sum * a[i].b);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
