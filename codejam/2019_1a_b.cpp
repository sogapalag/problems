#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
T exgcd(T a, T b, T& x, T& y) {
    if (!a) { x = 0; y = 1; return b; }
    T d = exgcd(b%a, a, y, x);
    x -= b/a * y;
    return d;
}
// watch out potential overflow!
template <typename T>
T crt(T a1, T a2, T n1, T n2) {
    T m1, m2;
    assert(exgcd<T>(n1,n2,m1,m2) == 1);
    T z = n1*n2;
    T res = (__int128)a1*m2%z*n2 %z + (__int128)a2*m1%z*n1 %z;
    ((res%=z)+=z)%=z;
    assert(res%n1 == a1%n1);
    assert(res%n2 == a2%n2);
    return res;
}

template <typename T>
T excrt(T a1, T a2, T n1, T n2) {
    T m1, m2;
    T g = exgcd<T>(n1,n2,m1,m2);
    assert(abs(a1-a2) % g == 0);
    T z = n1*n2/g;
    T res = a1 - (__int128)n1*m1%z*((a1-a2)/g)%z;
    ((res%=z)+=z)%=z;
    assert(res%n1 == a1%n1);
    assert(res%n2 == a2%n2);
    return res;
}
using ll=long long;
using vl = vector<ll>;
ll dummy(vl& a, vl& p){
    const int N = 1e6+10; 
    vector<int> cnt(N, 0);
    for (int i = 0; i < 7; i++) {
        for (int x = a[i]; x < N; x+=p[i]) {
            cnt[x]++;
        }
    }
    for (int x = 1; x < N; x++) {
        if (cnt[x] == 7) return x;
    }
}
// 7, 18, cycle, obvious hint crt.
// 2*3*5*7*11*13*17 ~ 5e5. since crt require pair-coprime, 2->4, already sat.1e6.
//   even though 3->9, 2->16. we can get larger bound.
void solve() {
    int n = 7;
    vector<ll> p = {3, 4, 5, 7, 11, 13, 17};
    vector<ll> a(n);
    auto query = [](ll x){
        for (int _ = 0; _ < 18; _++) {
            cout << x << ' ';
        }cout << endl;//'\n' << flush;
        ll sum = 0;
        for (int _ = 0; _ < 18; _++) {
            ll r; cin >> r;
            sum += r;
        }
        return sum % x;
    };
    for (int i = 0; i < n; i++) {
        a[i] = query(p[i]);
    }
    ll r = a[0], m = p[0];
    for (int i = 1; i < n; i++) {
        r = crt<ll>(r, a[i], m, p[i]);
        m *= p[i];
    }
    for (int i = 0; i < n; i++) {
        assert(r % p[i] == a[i]);
    }
    assert(dummy(a,p) == r);
    cout << r << endl;// << '\n' << flush;
    int verdict; cin >> verdict;
    assert(verdict == 1);
    if (verdict == -1) exit(-1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t,_n,_m;
    cin >> t >> _n >> _m;
    while(t--)solve();
    return 0;
    // ...additional endl, result WA.
    //cout << endl;
}
