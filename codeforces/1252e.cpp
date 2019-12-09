#include <bits/stdc++.h>

using namespace std;


// use simple greedy would consider bunch situation.
// key observation: note for each i, valid range consective [l..r]
void solve() {
    int n,L,R,K;
    cin >> n >> L >> R >> K;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    // deduce backwards
    vector<int> l(n), r(n);
    l[n-1] = L, r[n-1] = R;
    for (int i = n-2; i >= 0; i--) {
        if (a[i] == a[i+1]) {
            l[i] = l[i+1];
            r[i] = r[i+1];
        } else if (a[i] < a[i+1]) {
            l[i] = max(l[i+1]-K, L);
            r[i] = r[i+1] - 1;
        } else {
            l[i] = l[i+1] + 1;
            r[i] = min(r[i+1]+K, R);
        }
        if (l[i] > R || r[i] < L) {
            cout << -1; return;
        }
    }

    // greedy pick valid smallest
    int x = l[0];
    cout << x << ' ';
    for (int i = 1; i < n; i++) {
        if (a[i-1] < a[i]) {
            x = max(x+1, l[i]);
            assert(x <= r[i]);
        } else if (a[i-1] > a[i]){
            x = max(x-K, l[i]); // -K
            assert(x <= r[i]);
        }
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
