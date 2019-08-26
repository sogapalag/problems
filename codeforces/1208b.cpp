#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Compress {
    map<T, int> id;
    vector<T> num;

    inline int get_id(T x) {
        if (!id.count(x)) {
            id[x] = num.size();
            num.emplace_back(x);
        }
        return id[x];
    }
    inline int get_num(int i) {
        assert(0 <= i && i < num.size());
        return num[i];
    }
};

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    Compress<int> c;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = c.get_id(x);
    }
    int sz = c.num.size();
    if (sz == n) {
        cout << 0; return;
    }
    vector<int> pre(n, -1);
    vector<int> las(n, -1);
    for (int i = 0; i < n; i++) {
        pre[i] = las[a[i]];
        las[a[i]] = i;
    }
    vector<int> rig(n, -2), ht(n, -1);
    int R = -1;
    for (int i = n-1; i >= 0; i--) {
        if (rig[a[i]] == -1) rig[a[i]] = i;
        if (ht[a[i]] == -1) ht[a[i]] = i, rig[a[i]]++;
        R = max(R, rig[a[i]]);
    }
    int r = -1;
    int res = n;
    for (int i = 0; i < n; i++) {
        r = max(r, R);
        res = min(res, r - i + 1);
        //
        r = max(r, ht[a[i]]);
        if (pre[i] != -1) break;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
