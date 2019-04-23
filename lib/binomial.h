// precompute binomial table, O(N^N)
const ll MOD = 1e9 + 7;
const int N = 1005;
ll bino[N][N];
void bino_table(){
    F0R(i, N){
        bino[i][0] = 1;
        bino[i][i] = 1;
    }
    FOR(i, 1, N){
        FOR(j, 1, i){
            bino[i][j] = (bino[i-1][j-1] + bino[i-1][j]) % MOD;
        }
    }
}

