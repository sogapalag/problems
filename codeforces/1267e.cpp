#include <bits/stdc++.h>

using namespace std;
using pi=pair<int, int> ;

const int N = 128; 
int a[N][N];

// for each i, check make i>T
void solve() {
    int n,m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    int res = m;
    vector<int> certificate(m);
    iota(certificate.begin(), certificate.end(), 1);
    const int T = n-1; 
    for (int i = 0; i < n-1; i++) {
        priority_queue<pi> pq;
        int sum = 0;
        for (int j = 0; j < m; j++) {
            int d = a[j][T] - a[j][i];
            sum += d;
            pq.push({d, j+1});
        }
        int cnt = 0;
        vector<int> tmp;
        while (sum > 0) {
            auto mx = pq.top();
            sum -= mx.first; 
            tmp.push_back(mx.second);
            pq.pop();
            cnt++;
        }
        if (cnt < res) {
            res = cnt;
            certificate = tmp;
        }
    }
    cout << res << "\n";
    for (auto& x: certificate) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
