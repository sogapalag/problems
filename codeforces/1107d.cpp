#include <bits/stdc++.h>

using namespace std;
const int N = 5220; 
int8_t a[N][N];
void solve() {
    int n; cin >> n;
    auto hex_to_int = [](char x){
        return isdigit(x) ? x -'0' : x - 'A'+10;
    };
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        reverse(s.begin(), s.end());
        for (int j = 0; j < n; j++) {
            a[i][j] = (hex_to_int(s[j/4]) >> (j%4)) & 1;
        }
    }
    //cerr<<__gcd(0,0)<<endl;
    int g = 0;
    for(int _:{0,1}) {
        for (int i = 0; i < n; i++) {
            int8_t las = -1;
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (a[i][j] == las) cnt++;
                else {
                    g = __gcd(g, cnt);
                    las = a[i][j];
                    cnt = 1; // 1... not 0
                }
            }
            g = __gcd(g, cnt);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                swap(a[i][j], a[j][i]);
            }
        }
    }
    cout << g;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
