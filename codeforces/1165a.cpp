#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+5; 
char s[N];

void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    cin >> s;
    int res = 0;
    for (int i = n-1; i >= n-x; i--) {
        if (i != n-1-y && s[i] == '1'){
            res++;
        }
        if (i == n-1-y && s[i] == '0'){
            res++;
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
