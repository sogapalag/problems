#include <bits/stdc++.h>

using namespace std;


const int L = 15; 
const int N = 1<<L; 
int d[L][L];
//int ss[L][N];
int comp[N];
int dp[N][L];

int n,MSK;

//void sub_sum(int i){
//    vector<int> pos(n, 0); // [j..0] : + - - - - 
//    int sum = 0;
//    for (int j = 0; j < n; j++) {
//        pos[j] = d[i][j] - sum;
//        sum += d[i][j];
//    }
//    sum = 0;
//    // since ...1000 by ...0111 add +---
//    for (int msk = 1; msk < MSK; msk++) {
//        sum += pos[__builtin_ctz(msk)];
//        ss[i][msk] = sum;
//    }
//}

void calc_comp(){
    for (int msk = 0; msk < MSK; msk++) {
        for (int i = 0; i < n; i++) {
            if (!(msk&(1<<i))) continue;
            for (int j = i+1; j < n; j++) {
                if (!(msk&(1<<j))) continue;
                comp[msk] += d[i][j];
            }
        }
    }
}

void solve() {
    int m;
    cin >> n >> m;
    MSK = 1<<n;
    //memset(d, 0x3f, sizeof d);
    for (int _ = 0; _ < m; _++) {
        int x,y,c;
        cin >> x >> y >> c;
        x--;y--;
        d[x][y] = d[y][x] = c;
    }
    for (int i = 0; i < n; i++) {
        d[i][i] = 0;
    }
    //for (int i = 0; i < n; i++) {
    //    sub_sum(i);
    //}
    calc_comp();
    memset(dp, 0x3f, sizeof dp);
    dp[1][0] = 0;
    for (int msk = 1; msk < MSK; msk++) {
        // for [msk][j], remove (sub/j) - T
        for (int sub = msk; sub; (sub-=1)&=msk) {
            int T = msk^sub;
            for (int j = 0; j < n; j++) {
                if (sub & (1<<j)) {
                    // use ss, 5x slower
                    //int sum = 0;
                    //for (int i = 0; i < n; i++) {
                    //    if (i!=j && (sub & (1<<i)))
                    //        sum += ss[i][T];
                    //}
                    dp[msk][j] = min(dp[msk][j], dp[sub][j] - comp[sub^(1<<j)] - comp[T] +comp[msk^(1<<j)]);
                }
            }
        }
        // for [msk u i][i], remove (msk/j) - i
        for (int i = 0; i < n; i++) {
            if (msk & (1<<i)) continue;
            for (int j = 0; j < n; j++) {
                if ((msk & (1<<j)) && d[i][j]) {
                    dp[msk^(1<<i)][i] = min(dp[msk^(1<<i)][i], dp[msk][j] - comp[msk^(1<<j)] + comp[msk^(1<<j)^(1<<i)]);
                }
            }
        }
    }

    //for (int msk = 0; msk < MSK; msk++) {
    //    for (int i = 0; i < n; i++) {
    //        cout << dp[msk][i] << ' ';
    //    }cout << "\n";
    //}
    cout << dp[MSK-1][n-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
