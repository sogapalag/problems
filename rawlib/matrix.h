#include <bits/stdc++.h>

using namespace std;


typedef long long ll;

const ll MOD = 1000000007;

////////////////////////////////////////////
// b^e, b^-1, A^e, A*B; with mod.
//
//
//
////////////////////////////////////////////

ll mult(ll a, ll b, ll m=MOD){
    return ((a%m) * (b%m)) % m;
}
ll add(ll a, ll b, ll m=MOD){
    return (a%m + b%m) % m;
}
ll mpow(ll base, ll exp, ll m=MOD){
    ll res = 1;
    for (; exp; exp >>= 1){
        if (exp & 1)
            res = res*base % m;
        base = base*base % m;
    }
    return res;
}
ll inv(ll a, ll p=MOD){
    return mpow(a, p-2, p);
}

// A = A X B, 0-based, n:dim
const int COL = 101;
void mat_mult(ll n, ll A[][COL], ll B[][COL]){
    ll res[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = 0;
            for (int k = 0; k < n; k++) {
                res[i][j] += A[i][k] * B[k][j];
                if (res[i][j] >= MOD)
                    res[i][j] %= MOD;
            }
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = res[i][j];
}

// A = A^exp, n:dim
void mat_pow(ll n, ll A[][COL], ll exp){
    ll res[n][COL];
    memset(res, 0, sizeof res);
    for (int i = 0; i < n; i++)
        res[i][i] = 1;
    for(; exp; exp >>= 1){
        if (exp & 1)
            mat_mult(n, res, A);
        mat_mult(n, A, A);
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = res[i][j];
}
