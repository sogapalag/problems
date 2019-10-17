#include <bits/stdc++.h>

using namespace std;

struct Node {
    int x, y, z;
    Node() {}
    Node(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
    double dist(const Node& _oth) {
        double dx = x-_oth.x;
        double dy = y-_oth.y;
        double dz = z-_oth.z;
        return dx*dx+dy*dy+dz*dz;
    }
};

void solve() {
    int n; cin >> n;
    vector<Node> a(n);
    vector<bool> trk(n, false);
    for (auto& p: a) {
        cin >> p.x >> p.y >> p.z;
    }
    for (int i = 0; i < n; i++) {
        if (!trk[i]) {
            double mi = 1e25;
            int id;
            for (int j = 0; j < n; j++) {
                if (j!=i && !trk[j]) {
                    double d = a[i].dist(a[j]);
                    if (d < mi) {
                        mi = d;
                        id = j;
                    }
                }
            }
            trk[i] = true;
            trk[id] = true;
            cout << (i+1) << ' ' << (id+1) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
