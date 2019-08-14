#include <bits/stdc++.h>
using namespace std;
//~ SNIPPETS_START matrix_raw
namespace math {
    // A = A X B, 0-based, n:dim
    const int COL = 101;
    void mat_mult(int n, mint A[][COL], mint B[][COL]){
        mint res[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    res[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                A[i][j] = res[i][j];
    }
    
    // A = A^exp, n:dim
    void mat_pow(int n, mint A[][COL], long long exp){
        mint res[n][COL];
        memset(res, 0, sizeof res);
        for (int i = 0; i < n; i++)
            res[i][i] = 1;
        for(; exp; exp >>= 1){
            if (exp & 1)
                mat_mult(n, res, A);
            mat_mult(n, A, A);
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                A[i][j] = res[i][j];
    }
}
//~ SNIPPETS_END
