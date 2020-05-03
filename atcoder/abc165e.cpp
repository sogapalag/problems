#include <bits/stdc++.h>

using namespace std;


// key, a pair would use dist x, n-x
// we will find a partition disjoin dist. 1,2...,m
void solve() {
    int n,m;
    cin >> n >> m;
    int a = m/2;
    int b = m - a;
    int l = 1, r = l + a*2;
    int L = r+1, R = L + b*2-1;
    assert(R<=n);
    while (a--) {
        cout << l << ' ' << r << '\n';
        l++;r--;
    }
    while (b--) {
        cout << L << ' ' << R << '\n';
        L++;R--;
    }
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
