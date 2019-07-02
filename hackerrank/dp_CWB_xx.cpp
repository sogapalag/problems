#include <bits/stdc++.h>

using namespace std;

using ll=long long;

struct phash {
    size_t operator()(const pair<int8_t, int>& p) const {
        return hash<int8_t>()(p.first) ^ hash<int>()(p.second);
    }
};

unordered_map<pair<int8_t,int>, double, phash> dp;

#define ck(m, i) (((m) & (1<<(i))) > 0 )
#define clr(m, i) (((m)& ((1<<(i))-1)) | (((m)>>1) & ((-1)^((1<<(i))-1))) )

double f(int8_t n, int8_t k, int m) {
    if (k <= 0 || __builtin_popcount(m) == 0) return 0;
    if (dp.find({k, m}) != dp.end()) return dp[{k, m}];
    double sum = 0;
    for (int8_t i = 0; i < n/2; i++) {
        sum += 2 * max(ck(m,i) + f(n-1, k-1, clr(m, i)),
                       ck(m,n-1-i) + f(n-1, k-1, clr(m, n-1-i)));
    }
    if (n&1) sum += ck(m, n/2) + f(n-1, k-1, clr(m, n/2));
    sum /= n;
    dp[{k, m}] = sum;
    return sum;
}

// still TLE..need 2x faster
void solve() {
    int n, k; cin >> n >> k;
    int m = 0;
    for (int i = 0; i < n; i++) {
        char x; cin >> x;
        if (x == 'W') m |= 1<<i;
    }
    dp.reserve(1<<23);
    cout << fixed << setprecision(8) << f(n,k,m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
