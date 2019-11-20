#include <bits/stdc++.h>

using namespace std;
using ll=long long;
ll b, s;
ll n;
struct Node {
    ll x, y;
    Node() {}
    Node(ll _x, ll _y) : x(_x), y(_y) {}
    ll eval() {
        return x*s + y + b;
    }
};
double slope(Node& u, Node& v) {
    return (double)(v.y - u.y) / (double)(v.x - u.x);
}

void solve() {
    int m;
    cin >> n >> m;
    vector<Node> stk;
    b = s = 0;
    stk.emplace_back(0, 0);
    while (m--) {
        int op; cin >> op;
        if (op == 1) {
            int x; cin >> x;
            n += x;
            b = s = 0;
            stk.clear(); stk.emplace_back(0, 0);
        }
        if (op == 2) {
            int x; cin >> x;
            Node tmp = {n, -b - n*s};
            while (stk.size() >= 2) {
                auto it = --stk.end();
                auto jt = it; --jt;
                if (slope(*jt, *it) >= slope(*it, tmp)) {
                    stk.pop_back();
                } else break;
            }
            stk.push_back(tmp);
            n += x;
        }
        if (op == 3) {
            int _b, _s;
            cin >> _b >> _s;
            b += _b; s += _s;
        }
        while (stk.size() >= 2) {
            auto it = --stk.end();
            auto jt = it; --jt;
            if (jt->eval() <= it->eval()) {
                stk.pop_back();
            } else break;
        }
        auto it = --stk.end();
        cout << (it->x + 1) << ' ' << (it->eval()) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
