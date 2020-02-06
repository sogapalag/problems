#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// e.g. csacademy/candles
// problem: n bucket, with some capacity. wanna distribute k-color balls, #i-color = ci,
//   s.t. no same color into same bucket.
// ensure cap is sorted-dec.
bool is_distributed(const vector<int>& cap, const vector<int>& c) {
    int n = cap.size();
    vector<ll> freq(n+2);
    ll need = 0;
    for (int x: c) {
        if (x > n) return false;
        need += x;
        freq[x]++;
    }
    for (int i = n-1; i >= 0; i--) {
        freq[i] += freq[i+1];
    }
    ll could = 0;
    for (int i = 0; i < n; i++) {
        could += min((ll)cap[i], freq[i+1]);
        if (freq[i+1] > cap[i]) freq[i+2] += freq[i+1] - cap[i];
    }
    return could == need;
}
