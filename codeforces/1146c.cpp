#include <bits/stdc++.h>

using namespace std;

int q(int r, vector<int>& b) {
    cout << "1 " << b.size() << ' ';
    cout << r << ' ';
    for (auto& x: b) {
        cout << x << ' ';
    }
    cout << endl;
    int d; cin >> d;
    return d;
}

// there is a better solution using 7. and can ignore tree.
// note 2^7>100, write in bits, so ask 0-1 for each bit by partition setted or not.
// thus. we can sure each pair is covered
void solve() {
    int n; cin >> n;
    vector<int> candi(n-1);
    iota(candi.begin(), candi.end(), 2);

    // bs find r
    int mx = q(1, candi);
    while (candi.size() > 1) {
        vector<int> half;
        int m = candi.size();
        while (candi.size() > m/2) {
            half.push_back(candi.back());
            candi.pop_back();
        }
        if (q(1, half) == mx) candi = half;
    }
    int r = candi[0];
    candi.clear();
    for (int i = 1; i <= n; i++) {
        if (i != r) candi.push_back(i);
    }
    mx = q(r, candi);
    cout << "-1 " << mx << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
