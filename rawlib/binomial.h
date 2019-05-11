// precompute binomial table, O(N^N)

const long long MOD = 1e9 + 7;
const int N = 1005;

long long bino[N][N];

void bino_table() {
    for (int i = 0; i < N; i++) {
        bino[i][0] = 1;
        bino[i][i] = 1;
    }
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < i; j++) {
            bino[i][j] = (bino[i-1][j-1] + bino[i-1][j]) % MOD;
        }
    }
}

