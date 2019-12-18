#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int N = 14; 
ll fac[N];

// or an easy way, just enum all valid 47..4
ll f(ll n) {
    if (n < 4) return 0;
    string s = to_string(n);
    ll eq[2] = {0,1};
    for (char c:s){
        int x = c-'0';
        eq[0] = eq[0]*2 + eq[1]*((x>4)+(x>7));
        eq[1] = eq[1] * (x==4||x==7);
        eq[0] += 1; // leading zeros
    }
    return eq[0]+eq[1]-1;
}
bool is(ll n) {
    for (char c: to_string(n))if(c!='4'&&c!='7')return false;
    return true;
}

vector<int> get_kth_perm(int k, int n) {
    vector<int> p(n);
    vector<bool> trk(n);
    for (int i = 0; i < n; i++) {
        int c = k / fac[n-i-1];
        for (int j = 0; j < n; j++) {
            if(!trk[j]) {
                if (c == 0) {
                    p[i] = j; trk[j] = true;
                    break;
                } else {
                    c--;
                }
            }
        }
        k %= fac[n-i-1];
    }
    return p;
}

void solve() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i-1]*i;
    }
    ll n,k;
    cin >> n >> k;
    if (n<N && k > fac[n]) {
        cout << -1; return;
    }

    int i = 1;
    while (fac[i] < k) {
        i++;
    }
    k--;
    auto p = get_kth_perm(k, i);
    ll res = f(n-i);
    ll base = n-i+1;
    for (int j = 0; j < i; j++) {
        if (is(base+j) && is(base+p[j])) res++;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
