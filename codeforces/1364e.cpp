#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int query(int i, int j) {
    cout << "? " << i+1 << ' ' << j+1 << endl;
    int x; cin >> x;
    return x;
}
void solve() {
    int n; cin >> n;
    const int L = 32-__builtin_clz(n-1);
    // get index k-bit = 0
    vector<int> z(L,-1);
    while (count(z.begin(), z.end(), -1)) {
        int i = rng()%n;
        int j = rng()%n;
        if (i==j) continue;
        int x = query(i,j);
        for (int k = 0; k < L; k++) {
            if (x>>k&1) continue;
            z[k] = i;
        }
    }
    
    // p[i]?
    auto get = [&](int i){
        int res = (1<<L) - 1;
        for (int k = 0; k < L; k++) {
            if (i != z[k]) res &= query(i, z[k]);
            else res &= (1<<L)-1 - (1<<k); // 0
        }
        return res;
    };

    // find p[id] = 0
    int x = get(0);
    int id = 0;
    for (int i = 1; i < n && x > 0; i++) {
        // id sub i, more 0s
        if (query(i,id) == x) {
            x = get(id = i);
        }
    }

    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        if (i != id) res[i] = query(i, id);
    }
    cout << "! ";
    for (auto& x: res) {
        cout << x << ' ';
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
