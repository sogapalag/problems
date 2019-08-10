#include <bits/stdc++.h>

using namespace std;


// the poly = -(x^p - x) \sum_i 1/(x-i), a[i]=1
// proof:
//   note x^p-x = 0, i.e. x^p-x = (x-0)(x-1)...(x-p+1)
//   so for a[i]=1, we divide 1/(x-i)
//   and recall wilson's theorem, (p-1)! = -1.
//   thus (i-0)(i-1)...(i-p+1) = (p-1)! = -1. QED
//
// how to calc y=(x-x^p)/(x-i) ?
// a non-rigorous(physics) trick
// y = (1-x^{p-1})(1-i/x) = (1-x^{p-1}) * (1 + i/x + (i/x)^2 + ...)
// so we get coeff backwars, .... -i^2, -i^1, -1.
// for y[0], by wilson if i==0, y[0]=1, else, 0*..(i-1)(i+1).. = 0
// anyway, we can just don't care, cause we know final res[0] = a[0] for sure.
void solve() {
    int p; cin >> p;
    vector<int> a(p);
    for (auto& x: a) {
        cin >> x;
    }
    vector<int> res(p, 0);
    for (int i = 0; i < p; i++) {
        if (a[i] == 0) continue;
        vector<int> wil(p, 0);
        wil[p-1] = -1;
        if (i == 0) wil[0] = 1;
        else {
            for (int k = p-2; k >= 1; k--) {
                wil[k] = (wil[k+1] * i) % p;
            }
        }
        for (int k = 0; k < p; k++) {
            res[k] = (res[k] + wil[k]) % p;
        }
    }
    res[0] = a[0];
    for (int k = 0; k < p; k++) {
        res[k] = (res[k] + p) % p;
        cout << res[k] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
