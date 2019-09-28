#include <bits/stdc++.h>

using namespace std;

struct Node {
    double t, v;
    Node() {}
    Node(double _t, double _v) : t(_t), v(_v) {}
    Node& operator+=(const Node& _oth){
        t = (t*v + _oth.t*_oth.v)/(v+_oth.v);
        v += _oth.v;
        return *this;
    }
};

void solve() {
    int n; double L;
    cin >> n >> L;
    cout << fixed << setprecision(7);

    deque<Node> past; // sort by t
    double E = 0, V = 0; // total energy, volume
    for (int _ = 0; _ < n; _++) {
        double t, v;
        cin >> t >> v;
        // deprecated not need front.
        while (!past.empty() && V+v > L) {
            double depre = min(V+v-L, past[0].v);
            E -= depre * past[0].t;
            past[0].v -= depre;
            V -= depre;
            if (past[0].v <= 0.0000001) past.pop_front();
        }
        E += t*v; V += v;
        cout << E/V << "\n";

        past.emplace_back(t,v);
        int m = past.size();
        // merge pre larger t
        while (m>1 && past[m-2].t >= past[m-1].t) {
            past[m-2] += past[m-1];
            m--;
            past.pop_back();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
