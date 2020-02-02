#include <bits/stdc++.h>

using namespace std;
using ll=long long;
// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}
// there're IEP method, segtree method. also below bs could be optim to linear, omit. since much easier.
// first def AB[b] := max_{b_i>=b} a_i, i.e. if B doesn't hold > property, A would hold as long as A>AB[b].
//   consider a triangle XYZ, view AB as direct-edge(similar to 2-sat.)
//     X->Y, X->Z, Y->Z, this is exactly valid answer.
//     if (ai<X)Ix=0, => Iy=Iz=1
//     else Ix=1, Y->Z => at least Iy,Iz = 1
//   so naive calc is iter(x), iter(y|Ix=0), iter(z|Ix=0 or Iy=0), then a naive O(n^2) loop, 
//     bu notice r- max(ZX[x], ZY[y]), ZY[y] is dec.(any AB is dec), i.e. we just bs ZY[y] whether > ZX[x].
//        then we know which would contribute, by maintain prefix-sum.
// it's easy to argue included are valid, but one might confuse do we miss/exclude some valid?
//   just keep in mind, the only conditions, is the triangle, 0->1.
//   and the valid(x,y,z) sats. any (ai,bi,ci) with the triangle.
void solve() {
    int n, p,q,r;
    cin >> n >> p >> q >> r;
    vector<int> YX(p+1), ZX(p+1), ZY(q+1);
    for (int _ = 0; _ < n; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        YX[x] = max(YX[x], y);
        ZX[x] = max(ZX[x], z);
        ZY[y] = max(ZY[y], z);
    }
    for (int i = p-1; i >= 1; i--) {
        YX[i] = max(YX[i], YX[i+1]);
        ZX[i] = max(ZX[i], ZX[i+1]);
    }
    for (int i = q-1; i >= 1; i--) {
        ZY[i] = max(ZY[i], ZY[i+1]);
    }
    vector<ll> sumzy(q+1);
    for (int i = 1; i <= q; i++) {
        sumzy[i] = sumzy[i-1] + ZY[i];
    }

    ll res = 0;
    for (int x = 1; x <= p; x++) {
        int y = YX[x];
        if (y < q) {
            int z = ZX[x];
            int b = bs_last<int>(y+1, q+1, [&](int b){
                    return ZY[b] > z;
                    });
            res += r*1ll*(q-y);
            res -= (sumzy[b] - sumzy[y]);
            res -= (q-b) *1ll* z;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
