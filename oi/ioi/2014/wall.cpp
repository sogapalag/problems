#include <bits/stdc++.h>
#include "wall.h"
using namespace std;

const int INF = 1e9; 
const int N = 1<<21; 
int lb[N*2], ub[N*2];
void maxi(int& x, int y) {
    if (x < y) x = y;
}
void mini(int& x, int y) {
    if (x > y) x = y;
}
void apply(int i, int x, int y) {
    maxi(lb[i], x); maxi(ub[i], x);
    mini(lb[i], y); mini(ub[i], y);
}
void push(int i) {
    apply(i<<1, lb[i], ub[i]);
    apply(i<<1|1, lb[i], ub[i]);
    lb[i] = 0, ub[i] = INF;
}
void update(int l, int r, int x, int y, int i, int sl, int sr) {
    if (r <= sl || sr <= l) return;
    if (l <= sl && sr <= r) return apply(i, x, y);
    int sm = (sl+sr)>>1, il = i<<1, ir = i<<1|1;
    push(i);
    update(l, r, x, y, il, sl, sm);
    update(l, r, x, y, ir, sm, sr);
}
// think what if range_0 be cast(shrink) by another range_1
//   which is exactly "apply" func
void buildWall(int n, int k, int op[], int L[], int R[], int H[], int a[]) {
    for (int _ = 0; _ < k; _++) {
        if (op[_] == 1) {
            update(L[_], R[_]+1, H[_], INF, 1, 0, N);
        } else {
            update(L[_], R[_]+1, 0, H[_], 1, 0, N);
        }
    }
    // push_all
    for (int i = 1; i < N; i++) {
        push(i);
    }
    for (int i = 0; i < n; i++) {
        maxi(a[i], lb[i+N]);
        mini(a[i], ub[i+N]);
    }
}
