#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1.0); 
using cd = complex<double>;

// https://web.evanchen.cc/handouts/cmplx/en-cmplx.pdf
// let D,E,F be midpoint of arc BC, AC, AB
// then orthocenter of DEF is incenter of ABC
// so take average of D+E+F
void solve() {
    int n; double L;
    cin >> n >> L;
    vector<double> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cd res;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            res += polar(1.0, PI*(a[i]+a[j])/L) * (double)(n-j-1 + i);
            res += polar(1.0, PI*(a[i]+a[j])/L + PI) * (double)(j - i - 1);
        }
    }
    double tot = double(n)*(n-1)*(n-2)/6;
    res /= tot;
    cout << fixed << setprecision(10);
    cout << res.real() << ' ' << res.imag();
}
// simplify above formula by let a_k = exp(i pi x_i/L) 
// res = sum  a_i a_j (n-j-1+i) - (j-i-1) by e^ipi = -1
//     = sum ai aj (n-2j-2i)
//     = sum ai (2i) aj + ai(n-2j)aj
// so let f = sum ai 2i, g = sum ai
// we can get O(n) solution
void fast() {
    int n; double L;
    cin >> n >> L;
    cd res;
    cd f, g;
    for (int i = 0; i < n; i++) {
        double x; cin >> x;
        cd a = polar(1.0, PI*x/L);
        res += f * a + g  * double(n-2*i) * a;
        f += a * double(2*i);
        g += a;
    }
    double tot = double(n)*(n-1)*(n-2)/6;
    res /= tot;
    cout << fixed << setprecision(10);
    cout << res.real() << ' ' << res.imag();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //solve();
    fast();
    cout << endl;
}
