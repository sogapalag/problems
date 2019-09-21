#include <bits/stdc++.h>

using namespace std;

struct Event {
    int t, d, a;
    Event() {}
    Event(int _t, int _d, int _a) : t(_t), d(_d), a(_a) {}
    bool operator<(const Event& _oth) const {
        return t < _oth.t;
    }
};

// f(t,a) = g(l(t), r(t), x(t), a)
//        = l(t) + x(t),  a <= l(t)
//        = a  + x(t),    l(t) < a < r(t)
//        = r(t) + x(t),  r(t) < a
//
// in below the way calc seem strange. but imagine in a 'physics' way. (rigorous need some analytics)
//  first imagine we relax the bound [0,R] to (-oo, +oo), then x(t) shape does be the way calced
//  then when we add [0,R] bound to this. we can imagine (partial) ex(t)/et same (flip force remain),
//    it's just add a l(t) and r(t) force to this, in some seg calcel ex(t)/et to make a horitol line.
//
// so according to above, how to get new l(t)?
//      since l+x must in [0,R], implies l must in [-x, R-x]. so shrink it.
void solve() {
    int R, K;
    cin >> R >> K;
    vector<Event> es;
    for (int _ = 0; _ < K; _++) {
        int t; cin >> t;
        es.emplace_back(t, -1, 0);
    }
    int Q; cin >> Q;
    for (int _ = 0; _ < Q; _++) {
        int t,a;
        cin >> t >> a;
        es.emplace_back(t, 1, a);
    }
    sort(es.begin(), es.end());
    
    int l = 0, r = R, x = 0;
    int t = 0, d = -1;
    for (auto& e: es) {
        x += d * (e.t - t); t = e.t; d *= e.d;
        l = min(max(l,-x), -x+R);
        r = min(max(r,-x), -x+R);

        if (e.d > 0) {
            int a = min(max(e.a, l), r);
            cout << (a + x) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
