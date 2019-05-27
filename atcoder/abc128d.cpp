#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int res = 0;
    for (int i = 1; i <= min(k,n); i++) {
        int rem = k-i;
        for (int j = 0; j <= i; j++) {
            int tmp = 0;
            priority_queue<int, vector<int>, greater<int>> pq;
            for (int x = 0; x < j; x++) {
                tmp+=a[x];
                pq.push(a[x]); 
            }
            int x = n-1, r = i-j;
            while (r--) {
                tmp+=a[x];
                pq.push(a[x--]);
            }
            r = rem;
            while (r-- && !pq.empty()) {
                if (pq.top() < 0) tmp-=pq.top(), pq.pop();
                else break;
            }
            res = max(res, tmp);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
