#include <bits/stdc++.h>

using namespace std;


// fundamental thm. and fermart's x^p-x = 0
void solve() {
    int n; cin >> n;
    vector<int> a(n+1);
    for (int i = n; i >= 0; i--) {
        cin >> a[i];
    }
    const int N = 45000; // for future gcd prime factor out. need to this large
    vector<int> prime; prime.reserve(N);
    auto sieve = [&](){
        vector<bool> is(N+1, true);
        for (int p = 2; p*p <= N; p++) {
            if (is[p]) {
                for (int i = p*p; i <= N; i+=p) {
                    is[i] = false;
                }
            }
        }
        for (int p = 2; p <= N; p++) {
            if (is[p]) prime.emplace_back(p);
        }
    };
    sieve();
    auto check = [&](int p){
        if (a[0] % p) return false;
        for (int k = 1; k < p; k++) {
            int s = 0;
            for (int i = k; i <= n; i+=p-1) {
                s = (s+a[i]) % p;
            }
            s = (s+p) % p;
            if (s) return false;
        }
        return true;
    };
    // check divise x^p-x
    vector<int> res; res.reserve(N);
    for (int p: prime) {
        if (p <= n && check(p))
            res.emplace_back(p);
    }
    // check prime factor gcd, i.e. can make all coeff = 0
    int g = 0;
    for (int x: a) {
        g = __gcd(g, abs(x));
    }
    for (int p: prime) {
        if (g % p == 0) {
            res.emplace_back(p);
            while (g % p == 0) {
                g /= p;
            }
        }
    }
    if (g > 1) res.emplace_back(g); // prime > N
    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    for (int p: res) {
        cout << p << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
