#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    multiset<int> st;
    ll res = 0;
    int i=0;
    for (int _ = 0; _ < m; _++) {
        int x; cin >> x;
        if (!st.empty()) {
            auto it = st.find(x);
            if (it!=st.end()) {
                st.erase(it);
                res++;
                continue;
            }
        }
        while (a[i]!=x) {
            st.insert(a[i++]);
        }
        res += 2*st.size()+1;
        i++;
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
