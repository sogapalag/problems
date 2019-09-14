#include <bits/stdc++.h>

using namespace std;


// O(n)
void solve() {
    int n, X,Y;
    cin >> n >> X >> Y;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    const int INF = 0x3f3f3f3f;
    int sufA = 0;
    int sufB = INF;
    int res = abs(a[n] - Y);
    for (int i = n-1; i >= 1; i--) {
        int ta = abs(a[i] - a[n]); // A take i, B take n
        ta = min(ta, sufB);  // if B take (i, n)
        int tb = abs(a[i] - a[n]); // B take i, A take n
        tb = max(tb, sufA);  // if A take (i, n)
        sufA = max(sufA, ta);
        sufB = min(sufB, tb);
    }
    res = max(res, sufA);
    cout << res;
}

// O(1)
void solve2(){
    int n, X,Y;
    cin >> n >> X >> Y;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int res = abs(a[n] - Y);
    if (n>=2) res = max(res, abs(a[n-1]-a[n])); // if A leave two more, B can always achieve this too
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve2();
    cout << endl;
}
