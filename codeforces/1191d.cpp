#include <bits/stdc++.h>

using namespace std;

using ll=long long ;

// first move corner case.
// then final state 0, 1, 2,..,n-1
bool win() {
    int n; cin >> n;
    vector<int> a(n);
    ll sum = 0;
    for (auto& x: a) {
        cin >> x;
        sum += x;
    }
    if (sum == 0) return false;
    sort(a.begin(), a.end());
    if (n >=2 && a[1] == 0) return false;
    int eq = 0;
    int id = -1;
    for (int i = 1; i < n; i++) {
        if (a[i-1] == a[i]) {
            id = i-1;
            eq++;
        }
        if (eq >= 2) return false;
    }
    if (id >= 1 && a[id-1] + 1 == a[id]) return false;
    ll step = sum - (ll)n*(n-1)/2;
    return (step&1);

}
void solve() {
    cout << (win()? "sjfnb" : "cslnb");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
