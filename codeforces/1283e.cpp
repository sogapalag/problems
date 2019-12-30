#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    {// every 3 can into 1, and is lower bound since, x, y>=x+3 cannot be together
        int i = 0;
        int cnt = 0;
        while (i < n) {
            cnt++;
            int x = a[i];
            while (i<n && a[i] < x+3) {
                i++;
            }
        }
        cout << cnt << ' ';
    }
    {// greedy put -1,0,+1
        vector<bool> trk(n+2, false);
        for (int x: a) {
            if (!trk[x-1]) trk[x-1]=1;
            else if (!trk[x]) trk[x]=1;
            else trk[x+1]=1;
        }
        int cnt = 0;
        for (int x: trk) cnt+=x;
        cout << cnt;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
