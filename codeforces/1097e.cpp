#include <bits/stdc++.h>

using namespace std;
// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}
// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}
// greedy build antichains.
// Caution: return index;  although anti[.].back() inc. but they're not LIS. neither anti[.][0]
vector<vector<int>> antichain_decomp(const vector<int>& a) {
    vector<vector<int>> anti;
    int n = a.size();
    anti.emplace_back();
    anti[0].emplace_back(0);
    for (int i = 1; i < n; i++) {
        int k = bs_first<int>(0, anti.size(), [&](int k){
                return a[i] < a[anti[k].back()];
                });
        if (k == (int)anti.size()) {
            anti.emplace_back();
        }
        anti[k].emplace_back(i);
    }
    return anti;
}
// https://en.wikipedia.org/wiki/Longest_increasing_subsequence
// aka LIS. Caution: return index
vector<int> longest_chain(const vector<int>& a) {
    int n = a.size();
    vector<int> pre(n);
    vector<int> end(n+1);
    int len = 0;
    for (int i = 0; i < n; i++) {
        int l = len ? bs_last<int>(1, len+1, [&](int l){
                return a[end[l]] < a[i];
                }) : 0;
        pre[i] = end[l++];
        end[l] = i;
        if (l > len) len = l;
    }
    vector<int> res(len);
    for (int i = len-1, k = end[len]; i >= 0; i--) {
        res[i] = k; k = pre[k];
    }
    return res;
}

// Caution: return index.
pair<vector<int>, vector<vector<int>>> lis_anti(const vector<int>& a) {
    int n = a.size();
    vector<int> pre(n);
    vector<int> end(n+1);
    vector<vector<int>> anti;
    int len = 0;
    for (int i = 0; i < n; i++) {
        int l = len ? bs_last<int>(1, len+1, [&](int l){
                return a[end[l]] < a[i];
                }) : 0;
        pre[i] = end[l++];
        end[l] = i;
        if (l > len) len = l;
        if (l-1 == (int)anti.size()) anti.emplace_back();
        anti[l-1].emplace_back(i);
    }
    vector<int> res(len);
    for (int i = len-1, k = end[len]; i >= 0; i--) {
        res[i] = k; k = pre[k];
    }
    assert(res.size() == anti.size());
    return {res, anti};
}

// f[k]=k*(k+1)/2;
// for n in [f[k], f[k+1]). can divide to k gs.
// at least example.  1 | 3 2 | 6 5 4 | ...
// could. by Dilworth's thm either >k lis or <=k decomp
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int k = 1;
    while (n >= k*(k+1)/2) {
        k++;
    }k--;

    vector<vector<int>> res;
    while (true) {
        //auto anti = antichain_decomp(a);
        //auto lis = longest_chain(a);
        //assert(anti.size() == lis.size());
        auto [lis, anti] = lis_anti(a);
        int m = lis.size();
        if (m <= k) {
            //auto anti = antichain_decomp(a);
            for (auto& v: anti) {
                res.push_back(v);
                for (auto& x: res.back()) {
                    x = a[x];
                }
            }
            break;
        } else {
            res.emplace_back();
            vector<bool> trk(a.size());
            for (int i: lis) {
                res.back().push_back(a[i]);
                trk[i] = 1;
            }
            vector<int> b;
            for (int i = 0; i < (int)a.size(); i++) {
                if(!trk[i])b.push_back(a[i]);
            }
            swap(a, b); k--;
            if (a.empty()) break;
        }
    }

    cout << res.size() << "\n";
    for (auto& v: res) {
        cout << v.size() << ' ';
        for (auto& x: v) {
            cout << x << ' ';
        }cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
