#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

void solve() {
    int q;
    cin >> q;
    Tree<pair<int, int>> t;
    long long A = 0;
    long long B = 0;
    const int INF = 0x3f3f3f3f;
    int l=-INF, r=INF;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int a, b;
            cin >> a >> b;
            B += b;
            if (a < l) {
                A = A+l-a;
            }
            if (a > r) {
                A = A+a-r;
            }
            t.insert(make_pair(a, q));
            int n = t.size();
            l = (n-1)/2;
            r = (n&1)? l : l+1;
            l = t.find_by_order(l)->first;
            r = t.find_by_order(r)->first;
        } else {
            cout << l << ' ' << A+B << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
