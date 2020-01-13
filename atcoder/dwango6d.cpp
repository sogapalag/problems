#include <bits/stdc++.h>

using namespace std;


void __solve() {
    int n; cin >> n;
    vector<int> a(n), indeg(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        indeg[a[i]]++;
    }
    if (n == 2) {
        cout << -1; return;
    }
    set<int> bucket;
    set<pair<int,int>> lookup;
    for (int i = 0; i < n; i++) {
        bucket.insert(i);
        lookup.insert({indeg[i], i});
    }
    vector<int> p(n);
    vector<bool> trk(n);
    const int L = 3; 
    for (int i = 0; i < n-L; i++) {
        auto it = --lookup.end();
        int cnt,z;
        tie(cnt,z) = *it;
        for (int x: bucket) {
            if (i == 0 || a[p[i-1]] != x) {
                // if erase x, no invalid
                if (z == x || cnt - (i && a[p[i-1]]==z) < n-i-1) {
                    p[i] = x;
                    break;
                }
            }
        }
        if (i > 0) {
            int x = a[p[i-1]];
            if (!trk[x]) {
                lookup.erase({indeg[x],x});
                lookup.insert({--indeg[x], x});
            }
        }
        trk[p[i]] = true;
        bucket.erase(p[i]);
        lookup.erase({indeg[p[i]], p[i]});
    }

    for (int i = max(0, n-L); i < n; i++) {
        p[i] = *bucket.begin();
        bucket.erase(p[i]);
    }
    do {
        bool yes = true;
        for (int i = max(1, n-L); i < n; i++) {
            if (a[p[i-1]] == p[i]) yes = false;
        }
        if (yes) {
            for (int x: p) cout << x+1 << ' ';
            return;
        }
    } while (next_permutation(p.begin(), p.end()));
}

// the key is whenever we ensure no (max indeg)node that cannot put anywhere. i.e. deg = n-i-1. full
//   then we're fine till the end, except n=3, no u->v, v->u. case.  we can ignore that. use next_perm. 3! at most.
void solve() {
    int n; cin >> n;
    vector<int> a(n), indeg(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        indeg[a[i]]++;
    }
    if (n == 2) {
        cout << -1; return;
    }
    set<int> bucket;
    for (int i = 0; i < n; i++) {
        bucket.insert(i);
    }
    vector<int> p(n);
    vector<bool> trk(n);
    const int L = 3; 
    for (int i = 0; i < n-L; i++) {
        // cost is might need to find max-deg in the back.
        // don't happen much, since total deg <= n
        for (int x: bucket) {
            if (i == 0 || a[p[i-1]] != x) {
                // if erase x, no invalid
                if (trk[a[x]] || indeg[a[x]] - (i && a[p[i-1]]==a[x]) < n-i-1) {
                    p[i] = x;
                    break;
                }
            }
        }
        if (i > 0) {
            int x = a[p[i-1]];
            if (!trk[x]) indeg[x]--;
        }
        trk[p[i]] = true;
        bucket.erase(p[i]);
    }
    for (int i = max(0, n-L); i < n; i++) {
        p[i] = *bucket.begin();
        bucket.erase(p[i]);
    }
    do {
        bool yes = true;
        for (int i = max(1, n-L); i < n; i++) {
            if (a[p[i-1]] == p[i]) yes = false;
        }
        if (yes) {
            for (int x: p) cout << x+1 << ' ';
            return;
        }
    } while (next_permutation(p.begin(), p.end()));
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
