#include "sieve_st.h"
#include "transform_number_theory.h"

const int N = 100005; 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

Sieve s(2*N);
vector<int8_t> mu = s.mobius_table(2*N);

template <typename T>
inline vector<T> MT(const vector<T>& f) {
    int n = f.size();
    vector<T> F(n);
    for (int i = 1; i < n; i++) {
        for (int j = i; j < n; j+=i) {
            F[j] += f[i];
        }
    }
    return F;
}
template <typename T>
inline vector<T> MI(const vector<T>& F) {
    int n = F.size();
    vector<T> f(n);
    for (int i = 1; i < n; i++) {
        for (int j = i; j < n; j+=i) {
            f[j] += F[i] * mu[j/i];
        }
    }
    return f;
}
template <typename T>
inline vector<T> MTp(const vector<T>& f) {
    int n = f.size();
    vector<T> F(n);
    for (int i = 1; i < n; i++) {
        for (int j = i; j < n; j+=i) {
            F[i] += f[j];
        }
    }
    return F;
}
template <typename T>
inline vector<T> MIp(const vector<T>& F) {
    int n = F.size();
    vector<T> f(n);
    for (int i = 1; i < n; i++) {
        for (int j = i; j < n; j+=i) {
            f[i] += F[j] * mu[j/i];
        }
    }
    return f;
}
template <typename T>
inline void inplace_MIp(vector<T>& F) {
    int n = F.size();
    for (int i = n-1; i >= 1; i--) {
        for (int j = i*2; j < n; j+=i) {
            F[i] -= F[j];
        }
    }
}

using ll=long long;
bool test_mobius_inv() {
    int n = N + (rng()%N);
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) {
        a[i]=b[i]=rng();
    }
    a = MI(MT(a));
    for (int i = 1; i < n; i++) {
        if (a[i]!=b[i])return false;
    }
    a = MT(MI(a));
    for (int i = 1; i < n; i++) {
        if (a[i]!=b[i])return false;
    }
    return true;
}

bool test_superset() {
    int n = N + (rng()%N);
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) {
        a[i]=b[i]=rng();
    }
    a = MIp(MTp(a));
    for (int i = 1; i < n; i++) {
        if (a[i]!=b[i])return false;
    }
    a = MTp(MIp(a));
    for (int i = 1; i < n; i++) {
        if (a[i]!=b[i])return false;
    }
    return true;
}

bool test_inplace() {
    int n = N + (rng()%N);
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) {
        a[i]=b[i]=rng();
    }
    zeta(a); b=MT(b);
    for (int i = 1; i < n; i++) {
        if (a[i]!=b[i])return false;
    }
    mobius(a); b=MI(b);
    for (int i = 1; i < n; i++) {
        if (a[i]!=b[i])return false;
    }
    zeta_p(a); b=MTp(b);
    for (int i = 1; i < n; i++) {
        if (a[i]!=b[i])return false;
    }
    mobius_p(a); b=MIp(b);
    for (int i = 1; i < n; i++) {
        if (a[i]!=b[i])return false;
    }
    return true;
}

void solve() {
    assert(test_mobius_inv());
    assert(test_superset());
    assert(test_inplace());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
