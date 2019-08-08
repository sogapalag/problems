#include <bits/stdc++.h>

using namespace std;

int n;
string s;
vector<int> d1(n);
vector<int> d2(n);

// d1 odd, default 1
// d2 even, default 0, i as right
// radius
void manacher() {
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 1 : min(d1[l+r-i], r-i+1);
        while (0 <= i-k && i+k < n && s[i-k] == s[i+k]) {
            k++;
        }
        d1[i] = k--;
        if (i+k > r) {
            l = i-k;
            r = i+k;
        }
    }
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 0 : min(d2[l+r-i+1], r-i+1);
        while (0 <= i-k-1 && i+k < n && s[i-k-1] == s[i+k]) {
            k++;
        }
        d2[i] = k--;
        if (i+k > r) {
            l = i-k-1;
            r = i+k;
        }
    }
}
