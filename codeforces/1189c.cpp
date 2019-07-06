#include <bits/stdc++.h>

using namespace std;


struct Node {
    int r, c;
    Node() {}
    Node(int _r, int _c) : r(_r), c(_c) {}
};

Node st[18][100'005];


// by editorial, there is a math solution
// f = (sum a)/10
void solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        st[0][i] = {x, 0};
    }
    for (int j = 0; j < 17; j++) {
        for (int i = 0; i < n; i++) {
            if (i + (1 << (j+1)) > n) break;
            int sum = st[j][i].r + st[j][i + (1<<j)].r;
            int cdy = st[j][i].c + st[j][i + (1<<j)].c;
            st[j+1][i].r = sum % 10;
            st[j+1][i].c = cdy + (sum > 9);
        }
    }
    int q; cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        x--;
        int j = 31 - __builtin_clz(y - x);
        cout << st[j][x].c << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
