#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Compress {
    map<T, int> id;
    vector<T> num;

    Compress(vector<T> v) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        num = v;
        for (int i = 0; i < (int)num.size(); i++) {
            id[num[i]] = i;
        }
    }

    inline int get_id(T x) {
        assert(id.count(x));
        return id[x];
    }
    inline T get_num(int i) {
        assert(0 <= i && i < num.size());
        return num[i];
    }
};

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    Compress<> c(a);
    for (auto& x: a) {
        x = c.get_id(x);
    }
    int m = c.num.size();
    vector<int> L(m) , R(m);
    for (int i = 0; i < n; i++) {
        R[a[i]] = i;
    }
    for (int i = n-1; i >= 0; i--) {
        L[a[i]] = i;
    }
    int res = m-1;
    //for (int i = 1; i < m; i++) {
    //    if (R[i-1] > L[i]) break;
    //    res = min(res, m-1-i);
    //}
    //for (int i = m-1; i >= 1; i--) {
    //    if (R[i-1] > L[i]) break;
    //    res = min(res, i-1);
    //}
    int l = 0, r = 1;
    while (l < m) {
        if (r <= l) r = l+1;
        while (r < m && R[r-1] < L[r]) {
            r++;
        }
        res = min(res, m - (r-l));
        l++;
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
