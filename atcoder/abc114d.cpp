#include <bits/stdc++.h>

using namespace std;

long long C[26][26];
void pre(){
    memset(C, 0, sizeof C);
    C[0][0] = 1;
    for (int i = 1; i < 26; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i-1][j] + C[i-1][j-1];
        }
    }
}

void solve() {
    int n; cin >> n;
    vector<int> prime = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    vector<int> cnt(100, 0);
    auto decomp = [&](int x){
        for (int p: prime) {
            int e = 0;
            while (x % p == 0) {
                e++;
                x/=p;
            }
            cnt[p] += e;
            if (x == 1) break;
        }
    };
    for (int i = 1; i <= n; i++) {
        decomp(i);
    }
    int c3 = 0, c5 = 0, c15 = 0, c25 = 0, c75 = 0;
    for (int p: prime) {
        if (cnt[p] >= 2) c3++;
        if (cnt[p] >= 4) c5++;
        if (cnt[p] >= 14) c15++;
        if (cnt[p] >= 24) c25++;
        if (cnt[p] >= 74) c75++;
    }
    pre();
    // 3*5*5, 5*15, 3*25, 75
    int res = C[c5][2]*max(c3-2, 0) + c15*max(c5-1, 0) + c25*max(c3-1, 0) + c75;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
