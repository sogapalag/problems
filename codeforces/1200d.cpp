#include <bits/stdc++.h>

using namespace std;

const int N = 2111; 
int a[N][N];
int dp[N][N][2];


void solve() {
    int n, k;
    cin >> n >> k;
    memset(a, 0, sizeof a);
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        for (int j = 1; j <= n; j++) {
            a[i][j] += a[i][j-1] + (s[j-1]=='B');
        }
        for (int j = 1; j <= n; j++) {
            a[i][j] += a[i-1][j];
            //cout << a[i][j] << ' ';
        }
        //cout << "\n";
    }
    auto sum = [&](int i,int j, int x,int y){
        if (i > x || j > y) return 0;
        return a[x][y] - a[i-1][y] - a[x][j-1] + a[i-1][j-1];
    };
    auto R = [&](int row, int j, int y){
        return sum(row, j, row, y);
    };
    auto C = [&](int col, int i, int x){
        return sum(i, col, x, col);
    };
    auto r_all = [&](int row)->int{
        return R(row, 1, n) == 0;
    };
    auto c_all = [&](int col)->int{
        return C(col, 1, n) == 0;
    };
    auto r_cut = [&](int row, int j)->int{
        return R(row, 1, j-1)==0 && R(row, j+k, n)==0;
    };
    auto c_cut = [&](int col, int i){
        return C(col, 1, i-1)==0 && C(col, i+k, n)==0;
    };
    auto line = [&](int r, int c)->pair<int, int>{
        int row = 0, col = 0;
        for (int i = 1; i <= n; i++) {
            if (r<=i && i<= r+k-1) {
                row += (sum(i,1, i,c-1)==0 && sum(i,c+k,i,n)==0);
            }else {
                row += (sum(i,1, i, n) == 0);
            }
        }
        for (int j = 1; j <= n; j++) {
            if (c<=j && j<=c+k-1) {
                col += (sum(1,j, r-1,j)==0 && sum(r+k,j, n,j)==0);
            } else{
                col += (sum(1,j,n,j) == 0);
            }
        }
        return {row, col};
    };
    memset(dp, 0, sizeof dp);
   // for (int j = 1; j <= n-k+1; j++) {
   //     int r,c; tie(r,c) = line(1,j);
   //     dp[1][j][0] = r;
   //     dp[1][j][1] = c;
   // }
   // for (int i = 1; i <= n-k+1; i++) {
   //     int r,c; tie(r,c) = line(i,1);
   //     dp[i][1][0] = r;
   //     dp[i][1][1] = c;
   // }
   // for (int i = 2; i <= n-k+1; i++) {
   //     for (int j = 2; j <= n-k+1; j++) {
   //         int& tmp = dp[i][j][0];
   //         tmp += dp[i-1][j][0];
   //         tmp += -(sum(i-1, 1, i-1,j-1)==0 && sum(i-1,j+k,i-1,n)==0) + (sum(i-1, 1,i-1,n)==0);
   //         tmp += (sum(i+k-1, 1, i+k-1,j-1)==0 && sum(i+k-1, j+k, i+k-1,n)==0);
   //         int& col = dp[i][j][1];
   //         col += dp[i][j-1][1];
   //         col += -(sum(1,j-1, i-1,j-1)==0 && sum(i+k, j-1,n,j-1)==0) + (sum(1,j-1,n,j-1) == 0);
   //         col += (sum(1,j+k-1,i-1,j+k-1)==0 && sum(i+k, j+k-1, n, j+k-1)==0);
   //     }
   // }
    
    auto line2 = [&](int r, int c)->pair<int, int>{
        int row = 0, col = 0;
        for (int i = 1; i <= n; i++) {
            if (r<=i && i<= r+k-1) {
                row += r_cut(i, c);
            }else {
                row += r_all(i);
            }
        }
        for (int j = 1; j <= n; j++) {
            if (c<=j && j<=c+k-1) {
                col += c_cut(j, r);
            } else{
                col += c_all(j);
            }
        }
        return {row, col};
    };
    for (int j = 1; j <= n-k+1; j++) {
        int r,c; tie(r,c) = line2(1,j);
        dp[1][j][0] = r;
        dp[1][j][1] = c;
        //cout << r << c <<'.';
    }
    for (int i = 1; i <= n-k+1; i++) {
        int r,c; tie(r,c) = line2(i,1);
        dp[i][1][0] = r;
        dp[i][1][1] = c;
        //cout << r << c <<'.';
    }
    
    for (int i = 2; i <= n-k+1; i++) {
        for (int j = 2; j <= n-k+1; j++) {
            dp[i][j][0] = dp[i-1][j][0] - r_cut(i-1, j) + r_all(i-1) + r_cut(i+k-1, j) - r_all(i+k-1);
            dp[i][j][1] = dp[i][j-1][1] - c_cut(j-1, i) + c_all(j-1) + c_cut(j+k-1, i)- c_all(j+k-1);
            //cout << dp[i][j][0] << ','<< dp[i][j][1]<<';';
        }
    }


    int res = 0;

    for (int i = 1; i <= n-k+1; i++) {
        for (int j = 1; j <= n-k+1; j++) {
            res = max(res, dp[i][j][0] + dp[i][j][1]);
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
