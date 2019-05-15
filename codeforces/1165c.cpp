#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+5; 
char s[N];

void solve() {
	int n;
    cin >> n;
    cin >> s;
    string res; res.reserve(n);
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (i == n-1){
            k++;
            break;
        }
        if (s[i] == s[i+1]) {
            k++;
        }else{
            res.push_back(s[i]);
            res.push_back(s[i+1]);
            i++;
        }
    }
    cout << k << '\n';
    if (res.size()) cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
