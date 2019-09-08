#include <bits/stdc++.h>

using namespace std;


// sufficient but not necessary
// 8 4 4 4 3 2 1 1 
void wrong_solve() {
    int n; cin >> n;
    vector<int> a(1<<n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end(), greater<int>());
    for (int j = 0; j < n; j++) {
        int k = 1<<j;
        for (int i = 0; i < k; i++) {
            if (a[i] <= a[i+k]) {
                cout << "No"; return;
            }
        }
    }
    cout << "Yes";
}

void solve() {
    int n; cin >> n;
    multiset<int, greater<int>> st;
    const int N = 1<<n; 
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        st.insert(x);
    }
    multiset<int, greater<int>> pa;
    pa.insert(*st.begin()); st.erase(st.begin());
    for (int i = 0; i < n; i++) {
        int k=1<<i;
        vector<int> sn(k);
        int j=0;
        for (int x: pa) {
            auto it = st.upper_bound(x);
            if (it == st.end()) {
                cout << "No"; return;
            }
            sn[j++] = *it;
            st.erase(it);
        }
        for (int x: sn) pa.insert(x);
    }
    cout << "Yes";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
