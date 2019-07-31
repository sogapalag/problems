#include <bits/stdc++.h>

using namespace std;


// note nodes not in match, are IndSet. so the complement ensures no impossible.
// then stuck in find the max-match. only blossem algo. O(N^3)orO(N^1.5)
// don't over-complicate!
// for this problem, no need max-match. just simple match while new edge can.
// already ensure the exclude property, no more matching edge.
// 
// if the problem need slightly > n matching. then need differ (impossible/IndSet). thus require max-match.
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> match;
    vector<bool> trk(3*n+1, false);
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        if (!trk[x] && !trk[y]) {
            trk[x] = trk[y] = true;
            match.emplace_back(i);
        }
    }
    if ((int)match.size() >= n) {
        cout << "Matching\n";
        for (int i = 0; i < n; i++) {
            cout << match[i] << ' ';
        }
    } else {
        cout << "IndSet\n";
        int cnt = 0;
        for (int i = 1; i <= 3*n && cnt < n; i++) {
            if (!trk[i]) {
                cout << i << ' ';
                cnt++;
            }
        }
        assert(cnt == n);
    }
    cout << "\n";
    // no impossible
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
