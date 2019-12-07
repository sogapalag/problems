#include <bits/stdc++.h>

using namespace std;


// used sqrt, m [1..sq] then down s [sq..1]
// well this is overkill, can just bruteforce all s from fixed lim s=max(a).
// since s*(a.size) <= n. thus O(n) solution.
void solve() {
    int n; cin >> n;
    vector<int> cnt(n+1);
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        cnt[x]++;
    }
    vector<int> a;
    for (auto& x: cnt) {
        if (x) a.emplace_back(x);
    }

    // note fix s, for each color, valid distribution is consective [l..r]
    auto check = [&](int s){
        int cnt = 0;
        for (int x: a) {
            int b = x / (s-1), r = x % (s-1);
            if (b < r) return 0;
            cnt += b - (b-r)/s; // for those (s-1)*s, could rotate 90
        }
        return cnt;
    };
    int i;
    for (i = 1; i*i <= n; i++) {
        int res = check(n/i + 1);
        if (res) {
            assert(res == i);
            cout << res << "\n";
            return;
        }
    }
    for (int s = i; s >= 2; s--) {
        int res = check(s);
        if (res) {
            cout << res << "\n";
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
