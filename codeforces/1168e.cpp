#include <bits/stdc++.h>

using namespace std;


// method, by swap, passing delta(fix to make vi^=d,vj^=d)
// hard part is proof.
// https://www.luogu.com.cn/problemnew/solution/CF1168E
void solve() {
    int n; cin >> n;
    n = 1<<n;
    vector<int> a(n),p(n),q(n),pos(n),v(n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum ^= a[i];
        p[i] = q[i] = pos[i] = i;
    }
    if (sum != 0) {
        cout << "Fou"; return;
    }
    function<void(int,int)> fix = [&](int i, int j){
        int k = pos[a[i]^q[i]];
        if (k==i) return;
        swap(p[i],p[k]); swap(pos[p[i]], pos[p[k]]);
        if (k!=j) swap(q[k],q[j]), fix(k,j);
    };
    
    for (int i = 0; i < n; i++) {
        if (v[i] != a[i]) {
            int d = v[i]^a[i];
            v[i]^=d; v[i+1]^=d;
            fix(i,i+1);
        }
    }
    cout << "Shi\n";
    for (auto& x: p) {
        cout << x << ' ';
    }cout << '\n';
    for (auto& x: q) {
        cout << x << ' ';
    }cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
