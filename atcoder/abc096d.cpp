#include <bits/stdc++.h>

using namespace std;


// prime %5==1
void solve() {
    vector<int> prime;
    auto sieve = [&](int _n = 45000){
        vector<bool> is(_n+1, true);
        is[0] = is[1] = false;
        for (int p = 2; p*p <= _n; p++) {
            if (is[p]) {
                for (int i = p*p; i <= _n; i += p) {
                    is[i] = false;
                }
            }
        }
        for (int i = 2; i <= _n; i++) {
            if (is[i])
                prime.emplace_back(i);
        }
    };
    sieve();
    vector<int> candi;
    for (int p: prime){
        if (p%5==1)candi.emplace_back(p);
    }
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << candi[i] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
