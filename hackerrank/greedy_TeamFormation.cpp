#include <bits/stdc++.h>

using namespace std;


// for connected cnt c0,c1,..
// make seq as long as ci >= c_{i-1}
void solve() {
    int n; cin >> n;
    if (n==0) {
        cout << "0\n"; return;
    }
    map<int, int> cnt;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        cnt[x]++;
    }
    cnt[0x3f3f3f3f] = 1;
    int res = 1'000'006;
    vector<int> q;// act as queue
    int las = -0x3f3f3f3f;
    auto calc = [&](){
        int m = q.size();
        int i = 0;
        while (i < m) {
            int len = 0;
            for (int j = i; j < m; j++) {
                if (j==i || q[j-1] < q[j]) {// since we q[j]--, so use <
                    q[j]--; len++;
                } else break;
            }
            res = min(res, len);
            while (i < m && q[i] == 0) {
                i++;
            }
        }
    };
    for (auto& kv: cnt) {
        int x, y;
        tie(x, y) = kv;
        if (x != las+1) {
            calc();
            q.clear();
        }
        las = x;
        q.push_back(y);
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--)solve();
    cout << endl;
}
