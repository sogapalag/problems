#include <bits/stdc++.h>

using namespace std;

#define ones(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)
#define ctz(x) __builtin_ctz(x)
#define lbit(x) ((x)&(-(x)))
#define hbit(x) 1<<(31-__builtin_clz(x))
#define isp2(x) ((x) && !((x)&((x)-1)))
#define set(x, p) ((x) |= (1<<(p)))
#define unset(x, p) ((x) &= (~(1<<(p))))
#define flip(x, p) ((x) ^= (1<<(p)))
#define ck(x, p) ((x) & (1<<(p)))

const int L = 17; 
int seg[1<<L];

void build(int l, int r, int flag) {
    if (l+2 == r) return;
    int A = seg[l], B = seg[r-1];
    int p = -1;
    for (int i = 0; i < L; i++) {
        if (ck(A, i) ^ ck(B, i))
            p = i;
    }
    assert(p >= 0);
    unset(flag, p);
    int k = -1;
    for (int i = 0; i < L; i++) {
        if (ck(flag, i))
            k = i;
    }
    assert(k >= 0);
    int m = (l+r)>>1;
    int C = A;
    flip(C, k);  seg[m-1] = C;
    flip(C, p);  seg[m] = C;
    if (ck(A, p)) {
        for (int i = l+1; i < m-1; i++) {
            set(seg[i], p);
        }
        for (int i = m+1; i < r-1; i++) {
            unset(seg[i], p);
        }
    } else {
        for (int i = l+1; i < m-1; i++) {
            unset(seg[i], p);
        }
        for (int i = m+1; i < r-1; i++) {
            set(seg[i], p);
        }
    }
    build(l, m, flag);
    build(m, r, flag);
}

void solve() {
    int n, A, B;
    cin >> n >> A >> B;
    int p = 60 + ones(A) - ones(B);
    if (!(p&1)) {
        cout << "NO";
        return;
    }
    seg[0] = A;
    seg[(1<<n)-1] = B;
    build(0, 1<<n, (1<<n)-1);
    cout << "YES" << "\n";
    for (int i = 0; i < (1<<n); i++) {
        cout << seg[i] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
