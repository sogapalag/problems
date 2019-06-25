#include <bits/stdc++.h>

using namespace std;


void solve() {
    vector<int> prime;

// SNIPPETS_START mobius
auto mobius = [&](int _n = 1'000'006){
    vector<int> mu(_n+1, 1);
    int cnt, x;
    for (int i = 2; i <= _n; i++) {
        cnt = 0, x = i;
        for (const int& p: prime) {
            if (p*p > x) break;
            if (x % p == 0) {
                cnt++; x /= p;
            }
            if (x % p == 0) {
                mu[i] = 0; break;
            }
        }
        if (x != 1) cnt++;
        mu[i] *= (cnt&1)?-1:1;
    }
    return mu;
};
auto mu = mobius();
// SNIPPETS_END

}
