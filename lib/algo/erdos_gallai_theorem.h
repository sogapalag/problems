#include <bits/stdc++.h>

using namespace std;

// Erdős–Gallai theorem
// ensure a sorted-inc.
bool erdos_gallai(const vector<int>& a) {
    int n = a.size();
    long long L = 0, R = 0;
    for (int i = n-1, j = 0, k = 1; i >= 0; i--, k++) {
        L += a[i];
        while (j < i && a[j] < k) R += a[j++];
        while (j > i) R -= a[--j];   
        if (L - k*1ll*(k-1) > R + (i-j)*1ll*k) return false;
    }
    return true;
}
// check val is too big(1) or small(-1). or valid(0).
int erdos_gallai(const vector<int>& a, int val) {
    int n = a.size();
    long long L = 0, R = 0;
    for (int i = n-1, j = 0, k = 1; i >= 0; i--, k++) {
        L += a[i];
        while (j < i && a[j] < k) R += a[j++];
        while (j > i) R -= a[--j];   
        if (L - k*1ll*(k-1) > R + (i-j)*1ll*k) return a[i]<=val ? 1 : -1;
    }
    return 0;
}
