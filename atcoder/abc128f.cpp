#include <bits/stdc++.h>

using namespace std;


// let c=A-B>0, note in time order. jump at(k>=0)
// 0 -> A -> c -> A+c -> 2*c ->..-> A-(k-1)c -> kc -> A+kc = N-1
// take odd-even seprately
// 0->c->2c->..-> kc
// A=(N-1-kc) <-... <-(N-1-(k-1)c)...<- N-1-c <- N-1.
// thus problem <=> choose c>0, and k>=0, s.t.
// take start at 0, +c +2c ...+kc
// take end N-1, -c -2c ... -kc
// valid when those not collide,(conside whether N-1 % c) and A>C>0
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    long long res = 0;
    for (int c = 1; c < n-1; c++) {
        long long tmp = 0;
        for (int k = 0; (k+1)*c <=n-1; k++) {
            int A = n-1 - k*c;
            int B = A - c;
            if ((n-1)%c == 0 && 2*k > (n-1)/c - 1) {
                break;
            }
            if (B <= 0) break;
            tmp += 0ll + a[A] + a[k*c];
            res = max(res, tmp);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
