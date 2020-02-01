#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+10; 
const int L = 31; 
// sum length
int trie[N * L][2], cnt = 1;
int has[N * L];
void insert(int x) {
    int crt = 0;
    for (int i = L-1; i >= 0; i--) {
        int& to = trie[crt][x>>i&1];
        if (to == 0) to = cnt++;
        crt = to;
        has[crt]++;
    }
}
using ll=long long;
void solve() {
    int n,k;
    cin >> n >> k;
    int sum = 0;
    ll res = 0;
    insert(0);
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        sum ^= x;
        int ta = sum ^ k; // target prefix-equal
        int crt = 0;
        for (int i = L-1; i >= 0; i--) {
            int to;
            if(k>>i&1) {
                //
            } else {
                // at this bit > k
                to = trie[crt][(ta>>i&1)^1];
                res += has[to];
            }
            crt = to = trie[crt][ta>>i&1];
            if (crt == 0) break;
            if (i == 0) res += has[crt]; 
        }
        insert(sum);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
