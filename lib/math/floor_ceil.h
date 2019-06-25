#include <bits/stdc++.h>

using namespace std;

using ll=long long;

// sum_{k=0..<m} floor [ (nk+x)/m ]; when n=1, ans=x
ll calc(ll n, ll m, ll x) {
    ll d = __gcd(n, m);
    return x/d*d + ((n-1)*(m-1)+d-1) / 2;
}

// sum_{k=0..<n} floor [ sqrt(k) ]
ll calc(ll n) {
    ll a = 1;
    while ((a+1)*(a+1) <= n) {
        a++;
    }// a = floor sqrt(n)
    return n*a - (2*a*a*a + 3*a*a + a) / 6;
}

// sum_{k=0..<n} floor [ (ak+b)/c ]
ll calc(ll a, ll b, ll c, ll n) {
    if (!n) return 0;
    ll res = (a/c) * n*(n-1)/2 + (b/c) * n;
    a %= c; b %= c;
    ll t = a*n+b;
    return res + calc(c, t%c, a, t/c);
}
