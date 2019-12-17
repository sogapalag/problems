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

bool test_ranked() {
    int n = 15;
    const int MSK = 1<<n; 
    vector<ll> a(MSK), b(MSK);
    for (int i = 0; i < MSK; i++) {
        a[i] = b[i] = rng();
    }
    fast_subset_zeta_transform(a);
    auto B = get_all_ranked_subset_zeta_transform(b);
    for (int m = 0; m < MSK; m++) {
        int r = __builtin_popcount(m);
        b[m] = 0;
        for (int i = 0; i <= r; i++) {
            b[m] += B[i][m];
        }
    }
    for (int i = 0; i < MSK; i++) {
        if (a[i]!=b[i]) return false;
    }
    return true;
}

bool test_subset_convolution() {
    int n = 10;
    const int MSK = 1<<n; 
    const int LIM = 100005; 
    vector<ll> a(MSK), b(MSK);
    for (int i = 0; i < MSK; i++) {
        a[i] = b[i] = rng()%LIM;
    }
    vector<ll> c(MSK), d(MSK);
    for (int i = 0; i < MSK; i++) {
        c[i] = d[i] = rng()%LIM;
    }
    clock_t x = clock();
    fast_subset_convolution_direct_sum(a,c);
    clock_t y = clock();
    cerr << "fast convo: " << (double)(y-x) / CLOCKS_PER_SEC << endl;
    x = clock();
    naive_subset_convolution_direct_sum(b,d);
    y = clock();
    cerr << "naive convo: " << (double)(y-x) / CLOCKS_PER_SEC << endl;
    for (int i = 0; i < MSK; i++) {
        //cout << a[i] << ' '<<b[i] << "\n";
        if (a[i]!=b[i]) return false;
    }
    return true;
}

bool test_disjoin() {
    int n = 10;
    const int MSK = 1<<n; 
    const int LIM = 100005; 
    vector<ll> a(MSK), b(MSK);
    for (int i = 0; i < MSK; i++) {
        a[i] = b[i] = rng()%LIM;
    }
    vector<ll> c(MSK), d(MSK);
    for (int i = 0; i < MSK; i++) {
        c[i] = d[i] = rng()%LIM;
    }
    fast_subset_convolution_disjoin(a,c);
    fast_subset_convolution_disjoin(b,d);
    for (int i = 0; i < MSK; i++) {
        //cout << a[i] << ' '<<b[i] << "\n";
        if (a[i]!=b[i]) return false;
    }
    return true;
}
bool test_point_disjoin() {
    int n = 10;
    const int MSK = 1<<n; 
    const int LIM = 100005; 
    vector<ll> a(MSK), b(MSK);
    for (int i = 0; i < MSK; i++) {
        a[i] = b[i] = rng()%LIM;
    }
    vector<ll> c(MSK), d(MSK);
    for (int i = 0; i < MSK; i++) {
        c[i] = d[i] = rng()%LIM;
    }
    fast_subset_convolution_disjoin(a,c);
    int x = rng()%MSK; (x+=MSK)%=MSK;

    return a[x] == get_point_value_subset_disjoin(b,d,x);
}

#include "fwht.h"
bool test_or_fwht() {
    int n = 10;
    const int MSK = 1<<n; 
    const int LIM = 100005; 
    vector<ll> a(MSK);Boly<ll> b(MSK);
    for (int i = 0; i < MSK; i++) {
        a[i] = b[i] = rng()%LIM;
    }
    vector<ll> c(MSK);Boly<ll> d(MSK);
    for (int i = 0; i < MSK; i++) {
        c[i] = d[i] = rng()%LIM;
    }
    fast_subset_convolution_union(a, c);
    or_fwht<ll>(b); or_fwht<ll>(d);
    for (int i = 0; i < MSK; i++) {
        b[i] *= d[i];
    }
    or_fwht(b, true);
    for (int i = 0; i < MSK; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

bool test_and_fwht() {
    int n = 10;
    const int MSK = 1<<n; 
    const int LIM = 100005; 
    vector<ll> a(MSK);Boly<ll> b(MSK);
    for (int i = 0; i < MSK; i++) {
        a[i] = b[i] = rng()%LIM;
    }
    vector<ll> c(MSK);Boly<ll> d(MSK);
    for (int i = 0; i < MSK; i++) {
        c[i] = d[i] = rng()%LIM;
    }
    fast_superset_convolution_intersection(a, c);
    and_fwht<ll>(b); and_fwht<ll>(d);
    for (int i = 0; i < MSK; i++) {
        b[i] *= d[i];
    }
    and_fwht(b, true);
    for (int i = 0; i < MSK; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

void solve() {
    //assert(test_subset_zeta());
    assert(test_inv_subset_zeta());
    assert(test_superset_zeta());
    assert(test_inv_superset());
    assert(test_ranked());
    assert(test_subset_convolution());
    assert(test_disjoin());
    assert(test_or_fwht());
    assert(test_and_fwht());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
