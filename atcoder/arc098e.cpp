#include <bits/stdc++.h>

using namespace std;


// consider each as minimal, cut into segs
void solve() {
    int n,k,q;
    cin >> n >> k >> q;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int res = 2e9;
    for (int i = 0; i < n; i++) {
        int mi = a[i];
        vector<int> seg;
        vector<int> candi;
        for (int j = 0; j <= n; j++) {
            if (j == n || a[j] < mi) {
                if ((int)seg.size() >= k) {
                    sort(seg.begin(), seg.end());
                    copy(seg.begin(), seg.end()-k+1, back_inserter(candi));
                }
                seg.clear();
            } else {
                seg.emplace_back(a[j]);
            }
        }
        if ((int)candi.size() >= q) {
            sort(candi.begin(), candi.end());
            int tmp = candi[q-1] - candi[0];
            res = min(res, tmp);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
