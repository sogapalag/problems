#include <bits/stdc++.h>

using namespace std;
struct Edge {
    int u,v,d;
    Edge() {}
    Edge(int _u,int _v,int _d): u(_u),v(_v),d(_d){}
};

void solve() {
    int L; cin >> L;
    int n = 32-__builtin_clz(L);
    vector<Edge> e;
    for (int i = 1; i < n; i++) {
        e.emplace_back(i-1,i, 0);
        e.emplace_back(i-1,i,1<<(i-1));
    }
    int crt = 1 << (n-1);
    L -= crt;
    while (L) {
        int h = 31-__builtin_clz(L);
        e.emplace_back(h, n-1, crt);
        L -= 1<<h;
        crt+= 1<<h;
    }
    int m = e.size();
    cout << n << ' ' << m <<"\n";
    for (auto& x: e) {
        cout << x.u+1 << ' '<<x.v+1<<' '<<x.d<<"\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
