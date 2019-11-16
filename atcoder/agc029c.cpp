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

// greedy min s[i] lexi
// stk record last string's val!=1 's  pos/val
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int res = bs_first<int>(1, n+1, [&](int k){
            if (k == 1) {
                for (int i = 1; i < n; i++) {
                    if (a[i-1] >= a[i]) return false;
                }
                return true;
            }
            vector<pair<int, int>> stk;
            for (int i = 1; i < n; i++) {
                if (a[i-1] >= a[i]) {
                    int pos = a[i];
                    // ignore futher to fill 1..11
                    while (!stk.empty() && stk.back().first > pos) {
                        stk.pop_back();
                    }
                    // carry, so replace with 1
                    while (!stk.empty() && stk.back().first == pos && stk.back().second == k) {
                        pos--;
                        stk.pop_back();
                    }
                    if (pos == 0) return false;
                    if (!stk.empty() && stk.back().first == pos) {
                        stk.back().second++;
                    } else stk.emplace_back(pos, 2);
                }
            }
            return true;
            });
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
