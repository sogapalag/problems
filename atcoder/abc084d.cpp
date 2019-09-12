#include <bits/stdc++.h>

using namespace std;

struct Sieve {
    int sz;
    vector<bool> is;
    vector<int> prime;
    Sieve(int n = 45000):sz(n) {
        prime.reserve(n/6);
        is.assign(n+1, true);
        is[0] = is[1] = false;
        for (int p = 2; (int64_t)p*p <= n; p++) {
            if (is[p]) {
                for (int i = p*p; i <= n; i += p) {
                    is[i] = false;
                }
            }
        }
        for (int i = 2; i <= n; i++) {
            if (is[i])
                prime.emplace_back(i);
        }
    }
};
const int N = 100005; 
int a[N];

void pre(){
    Sieve s(N);
    for (int i = 3; i <= 100000; i++) {
        a[i] = a[i-1];
        if (s.is[i] && s.is[(i+1)/2]) {
            a[i] += 1;
        }
    }
}

void solve() {
    pre();
    int q; cin >> q;
    while (q--) {
        int l,r;
        cin >> l >> r;
        l = max(l,3);
        if (l > r) {
            cout << "0\n";
        }else{
            cout << (a[r]-a[l-1]) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
