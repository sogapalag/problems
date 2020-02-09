#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
using ll=long long;
using pnt=pair<ll,ll>;
pnt operator-(pnt a, pnt b){
    return {a.x-b.x, a.y-b.y};
}
pnt operator+(pnt a, pnt b){
    return {a.x+b.x, a.y+b.y};
}
ll absq(pnt& p) {
    return p.x*p.x + p.y*p.y;
}
const ll LIM = 1500000ll * 1500000;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// determ. method, omit note 3-ray(+-) => 6ray in circle, \E some <=60degree, i.e. <= radius
void solve() {
    int n; cin >> n;
    vector<pnt> a(n);
    for (auto& p: a) {
        cin >> p.x >> p.y;
    }
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    bool found = false;
    vector<int> res(n);
    do {
        shuffle(id.begin(), id.end(), rng);
        pnt now = {0,0};
        for (int i: id) {
            pnt p0 = now + a[i];
            pnt p1 = now - a[i];
            int r;
            if (absq(p0) == absq(p1)) {
                r = rng()%2; r = r?1:-1;
            } else if (absq(p0) < absq(p1)) {
                r = 1;
            } else r = -1;
            
            res[i] = r;
            now = r==1?p0:p1;
        }
        if (absq(now) < LIM) found = true;
    } while (!found);
    for (auto& x: res) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
