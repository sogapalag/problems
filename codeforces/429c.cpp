#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end(), greater<int>());
    if (a[0]!=n || (n>1 && a[0]==a[1]) || (a[(n-1)/2]!=1)) {
        cout << "NO"; return;
    }
    
    vector<int> fre(n);
    function<bool(int)> dfs = [&](int i){
        if (i == n) {
            for (int j = 0; j < n; j++) {
                if (fre[j]) return false;
            }
            return true;
        }
        int sz = a[i];
        fre[i] = sz-1;
        for (int j = 0; j < i; j++) {
            if (a[j]-1 == sz) return false;// only one son
            if (fre[j] < sz) continue;
            fre[j] -= sz;
            if (dfs(i + 1)) return true;
            fre[j] += sz;
            
            if (sz == 1) break; // must needed, otherwise TLE
            // since half =1, and remain all leaves connect to any pa is same.
        }
        return false;
    };
    fre[0] = n-1;
    cout << (dfs(1)?"YES":"NO");

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
