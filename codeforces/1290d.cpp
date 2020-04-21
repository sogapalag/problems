#include <bits/stdc++.h>

using namespace std;


// note for each two pair of m/2 block, query which in a row, would ensure latter no same of former
// so brute-force all pair, can be done in 2n^2/k
// can actually be done in cosntant 1<=1.5
// key: 1-2-3-4-5-6 <=> 1-2,2-3,..4-5,5-6
//   each number repre a block, i.e. query in a row, has same effect of pair.
// so problem become find a partition of disjoin path of complete graph K
// below use zig-zag pattern s,s-1,s+1,s-2,s+2,..
// note below block size=m, since [m/2|m/2]_i,  [m/2|m/2]_j, would call twice (i,j) (j,i)
// one might argue there're i0-j0 i1-j1 edge aren't covered.
// well it's valid, focus item, each (x,y) distance <= m in (i,j)or(j,i)
void solve() {
    int n,m;
    cin >> n >> m;
    vector<bool> trk(n, true);
    auto q = [&](int i){
        if (!trk[i]) return;
        cout << "? " << i+1 << endl;
        char c; cin >> c;
        trk[i] = c == 'N';
    };
    int k = n/m;
    for (int i = 0; i < k; i++) {
        cout << 'R' << endl;
        int s = i;
        int d = 0;
        for (int _ = 0; _ < k; _++) {
            int l = (s+d+k)%k;
            l *= m;
            int r = l + m;
            while (l < r) q(l++);
            if (d >= 0) ++d;
            d = -d;
        }
    }
    int res = 0;
    for (int x:trk) res += x;
    cout << "! " << res << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
