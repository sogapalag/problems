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
}s(3e3);

// a cycle deg=2, prime.
// note deg=3 is prime too, and we wanna m prime, we can add n/2 pair, since prime density,[n, n+n/2) should has prime inside
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> es;
    for (int i = 0; i < n; i++) {
        es.emplace_back(i, (i+1)%n);
    }
    int i = 0;
    while (!s.is[es.size()]) {
        assert(i < n/2);
        es.emplace_back(i, i + n/2);
        i++;
    }
    cout << es.size() << "\n";
    for (auto& _: es) {
        int x,y;
        tie(x,y) = _;
        x++;y++;
        cout << x << ' ' << y << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
