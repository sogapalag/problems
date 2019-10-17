#include <bits/stdc++.h>

using namespace std;


// another method, let pa=b, p=ba^-1
// i is iff p_i < max(..p_i)
void solve() {
    int n; cin >> n;
    set<pair<int,int>> st;
    vector<int> ord(n+1);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        st.emplace(i, x);
        ord[x] = i;
    }
    int cnt = 0;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        pair<int, int> p = {ord[x], x};
        if (*st.begin() != p) cnt++;
        st.erase(p);
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
