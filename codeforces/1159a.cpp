#include <bits/stdc++.h>

using namespace std;

void solve() {
	int n;
    cin >> n;
    string s;
    cin >> s;
    for (int i = 0; i <= n; i++) {
        int x = i;
        bool flag = true;
        for (char c: s){
            if (c == '-') {
                x--;
            }else{
                x++;
            }
            if (x < 0) {
                flag = false;
                break;
            }
        }
        if (flag) {
            cout << x; return;
        }
    }
}

int main() {
    //~ ios_base::sync_with_stdio(false);
    //~ cin.tie(NULL);
    solve();
    cout << endl;
}
