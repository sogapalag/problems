#include <bits/stdc++.h>

using namespace std;


void solve() {
    int K, X, Y;
    cin >> K >> X >> Y;
    bool is_nx = X < 0;
    bool is_ny = Y < 0;
    int neg[2] = {1, -1};
    X = abs(X), Y = abs(Y);
    bool is_sw = X > Y;
    if (is_sw) {
        swap(X, Y);
    }
    if (K%2 == 0 && (X+Y)%2 == 1) {
        cout << -1; return;
    }
    int i = 1;
    // B int, >= 0, and if i=1, obviously B cannot >0
    while ((i*K-X-Y)%2 != 0 || (i*K-X-Y) < 0 || (i==1 && (i*K-X-Y)>0)) {
        i++;
    }
    int A = (i*K + X+Y)/2;
    int B = (i*K - X-Y)/2;
    vector<pair<int, int>> res; res.reserve(i);
    int cx = 0, cy = 0;
    // consume oppsite direction move.
    while (B > 0) {
        while (B >= K) {
            cy -= K;
            res.emplace_back(cx, cy);
            B -= K;
        }
        while (B > 0) {
            cx -= B;
            cy += K-B;
            res.emplace_back(cx, cy);
            A -= K-B;
            B -= B;
        }
    }
    assert(B == 0);
    // consume positive direction move.
    while (A > 0) {
        while (X > cx) {
            while (X - cx >= K) {
                cx += K;
                res.emplace_back(cx, cy);
                A -= K;
            }
            while (X > cx) {
                int dx = X - cx;
                cx += dx; cy += K-dx;
                res.emplace_back(cx, cy);
                A -= K;
            }
        }
        assert(X == cx);
        assert((Y-cy) % K == 0);
        while (Y > cy) {
            cy += K;
            res.emplace_back(cx, cy);
            A -= K;
        }
    }
    assert(A == 0);
    assert(i == (int)res.size());

    cout << i << "\n";
    for (int j = 0; j < i; j++) {
        int x, y;
        tie(x, y) = res[j];
        if (is_sw) {
            swap(x, y);
        }
        x *= neg[is_nx];
        y *= neg[is_ny];
        cout << x << ' ' << y << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
