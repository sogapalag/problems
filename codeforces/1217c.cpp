#include <bits/stdc++.h>

using namespace std;

const int L = 18; 

void solve() {
    string s; cin >> s;
    int n = s.size();
    vector<int> sum(n+1);
    sum[0]=0;
    for (int i = 0; i < n; i++) {
        sum[i+1] = sum[i] + (s[i]-'0');
    }
    long long res = 0;
    for (int r = n-1; r >= 0; r--) {
        int x = 0;
        for (int j = 0; j < L; j++) {
            if (r-j < 0) break;
            if (s[r-j]=='1') {
                x |= (1<<j);
                if (x < j+1) continue;
                int y = x-j-1;
                if (r-j-y>=0 && sum[r-j]-sum[r-j-y]==0) {
                    res++;
                }
            }
        }
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
