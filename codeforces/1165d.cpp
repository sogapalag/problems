#include <bits/stdc++.h>

using namespace std;

void solve() {
	int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> d(n);
        for (auto& x: d) {
            cin >> x;
        }
        sort(d.begin(), d.end());
        long long res = d[0] * d[n-1];
        bool flag = true;
        for (int i = 0; i < n; i++) {
            if (d[i]*d[n-i-1] != res){
                flag = false; break;
            }
        }
        if (!flag){
            cout << "-1\n";
        }else{
            int cnt = 0;
            long long i = 2;
            for (; i*i <= res; i++){
                if (res % i == 0) cnt++;
            }
            if (cnt != (n+1)/2){
                cout << "-1\n";
            }else{
                cout << res << "\n";
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
