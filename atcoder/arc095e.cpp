#include <bits/stdc++.h>

using namespace std;

int n,m;
int FULL;
char S[12][12];
char s[12][12];

inline void cpy_r(int r, int i) {
    for (int j = 0; j < m; j++) {
        s[r][j] = S[i][j];
    }
}
bool used[12];
// check col rev match
void ck_col() {
    memset(used, 0, sizeof used);
    bool mid_find = !(m&1);
    for (int j = 0; j < m; j++) {
        if (used[j]) continue;
        bool find=false;
        for (int k = j+1; k < m; k++) {
            if (used[k]) continue;
            bool rev=true;
            for (int i = 0; i < n; i++) {
                if (s[i][j] != s[n-1-i][k]) {rev=false;break;}
            }
            if (rev) {
                find = true;
                used[j]=used[k]=true;
                break;
            }
        }
        if (!find) {
            if (mid_find) return;
            for (int i = 0; i < n; i++) {
                if (s[i][j] != s[n-1-i][j]) return;
            }
            mid_find = true;
            used[j] = true;
        }
    }
    cout<<"YES"<<endl; exit(0);
}
// enume 11*9*7*5*3 pair
void enume(int msk, int L) {
    if (msk == FULL) {
        ck_col();
    }
    int i=0;
    while (msk&(1<<i)) {
        i++;
    }
    cpy_r(L, i); msk |= 1<<i; i++;
    for (int k = i; k < n; k++) {
        if (msk & (1<<k)) continue;
        cpy_r(n-1-L, k);
        enume(msk|(1<<k), L+1);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> S[i];
    }
    FULL = (1<<n)-1;
    if (n&1) {
        for (int i = 0; i < n; i++) {
            cpy_r(n/2, i);
            enume(1<<i, 0);
        }
    } else {
        enume(0, 0);
    }
    cout << "NO";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
