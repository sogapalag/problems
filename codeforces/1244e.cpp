#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// let x,y be length(of same val) pre/suf
// since x... cost slop inc. so does y.
// so greedy pick smaller of x,y
void solve() {
    int n; ll k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    int i = 0, j = n-1;
    while (i+1 < n && a[i+1] == a[i]) {
        i++;
    }
    while (j-1 >= 0 && a[j-1] == a[j]) {
        j--;
    }

    while (i < j && k > 0) {
        int x = i+1;
        int y = n-j;
        if (x < y) {
            ll d = a[i+1] - a[i];
            if (k >= d*x) {
                k -= d*x;
                i++;
                while (i+1 < n && a[i+1] == a[i]) {
                    i++;
                }
            } else {
                a[i] += k/x; break;
            }
        } else {
            ll d = a[j] - a[j-1];
            if (k >= d*y) {
                k -= d*y;
                j--;
                while (j-1 >= 0 && a[j-1] == a[j]) {
                    j--;
                }
            } else {
                a[j] -= k/y; break;
            }
        }
    }
    int res = i<j?a[j]-a[i]:0;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
