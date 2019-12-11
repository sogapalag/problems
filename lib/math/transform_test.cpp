#include "transform.h"
using ll=long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool test_subset_zeta() {
    int n = 17;
    const int MSK = 1<<n; 
    vector<ll> a(MSK), b(MSK);
    for (int i = 0; i < MSK; i++) {
        a[i] = b[i] = rng();
    }
    clock_t x = clock();
    a = naive_subset_zeta_transform(a);
    clock_t y = clock();
    cerr << "naive zeta: " << (double)(y-x) / CLOCKS_PER_SEC << endl;
    x = clock();
    fast_subset_zeta_transform(b);
    y = clock();
    cerr << "fast zeta: " << (double)(y-x) / CLOCKS_PER_SEC << endl;
    for (int i = 0; i < MSK; i++) {
        //cout << a[i]<<','<<b[i]<<"\n";
        if (a[i]!=b[i]) return false;
    }
    return true;
}
bool test_inv_subset_zeta() {
    int n = 15;
    const int MSK = 1<<n; 
    vector<ll> a(MSK), b(MSK);
    for (int i = 0; i < MSK; i++) {
        a[i] = b[i] = rng();
    }
    clock_t x = clock();
    fast_subset_zeta_transform(a);
    clock_t y = clock();
    cerr << "zeta: " << (double)(y-x) / CLOCKS_PER_SEC << endl;
    x = clock();
    fast_subset_mobius_transform(a);
    y = clock();
    cerr << "mobius: " << (double)(y-x) / CLOCKS_PER_SEC << endl;
    // MZ
    for (int i = 0; i < MSK; i++) {
        //cout << a[i]<<','<<b[i]<<"\n";
        if (a[i]!=b[i]) return false;
    }
    // ZM
    fast_subset_mobius_transform(a);
    fast_subset_zeta_transform(a);
    for (int i = 0; i < MSK; i++) {
        //cout << a[i]<<','<<b[i]<<"\n";
        if (a[i]!=b[i]) return false;
    }
    return true;
}

bool test_superset_zeta() {
    int n = 15;
    const int MSK = 1<<n; 
    vector<ll> a(MSK), b(MSK);
    for (int i = 0; i < MSK; i++) {
        a[i] = b[i] = rng();
    }
    fast_superset_zeta_transform(a);
    map_complement(b);
    fast_subset_zeta_transform(b);
    map_complement(b);
    // Z' = rZr
    for (int i = 0; i < MSK; i++) {
        //cout << a[i]<<','<<b[i]<<"\n";
        if (a[i]!=b[i]) return false;
    }
    fast_subset_zeta_transform(a);
    map_complement(b);
    fast_superset_zeta_transform(b);
    map_complement(b);
    // Z = rZ'r
    for (int i = 0; i < MSK; i++) {
        //cout << a[i]<<','<<b[i]<<"\n";
        if (a[i]!=b[i]) return false;
    }
    return true;
}

bool test_inv_superset() {
    int n = 15;
    const int MSK = 1<<n; 
    vector<ll> a(MSK), b(MSK);
    for (int i = 0; i < MSK; i++) {
        a[i] = b[i] = rng();
    }
    fast_superset_zeta_transform(a);
    fast_superset_mobius_transform(a);
    // M'Z' = I
    for (int i = 0; i < MSK; i++) {
        //cout << a[i]<<','<<b[i]<<"\n";
        if (a[i]!=b[i]) return false;
    }
    fast_superset_mobius_transform(a);
    fast_superset_zeta_transform(a);
    // Z'M' = I
    for (int i = 0; i < MSK; i++) {
        //cout << a[i]<<','<<b[i]<<"\n";
        if (a[i]!=b[i]) return false;
    }
    return true;
}

bool test_superset_mobius() {
    int n = 15;
    const int MSK = 1<<n; 
    vector<ll> a(MSK), b(MSK);
    for (int i = 0; i < MSK; i++) {
        a[i] = b[i] = rng();
    }
    fast_superset_mobius_transform(a);
    map_complement(b);
    fast_subset_mobius_transform(b);
    map_complement(b);
    // M' = rMr
    for (int i = 0; i < MSK; i++) {
        //cout << a[i]<<','<<b[i]<<"\n";
        if (a[i]!=b[i]) return false;
    }
    fast_subset_mobius_transform(a);
    map_complement(b);
    fast_superset_mobius_transform(b);
    map_complement(b);
    // M = rM'r
    for (int i = 0; i < MSK; i++) {
        //cout << a[i]<<','<<b[i]<<"\n";
        if (a[i]!=b[i]) return false;
    }
    return true;
}


void solve() {
    //assert(test_subset_zeta());
    assert(test_inv_subset_zeta());
    assert(test_superset_zeta());
    assert(test_inv_superset());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
