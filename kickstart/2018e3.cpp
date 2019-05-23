#include <bits/stdc++.h>

using namespace std;

struct Node {
    int x, y, z, s;
    Node(int _x, int _y, int _z) : x(_x), y(_y), z(_z), s(0){}
};
int n;
void dfs(vector<Node>& C, vector<int>& c, int i=0, int cx=0, int cy=0, int cz=0, int sx=0, int sy=0, int sz=0){
    if (i == 3*n) {
        C.emplace_back(sx, sy, sz);
        return;
    }
    if (cx < n) dfs(C, c, i+1, cx+1, cy, cz, sx+c[i], sy, sz);
    if (cy < n) dfs(C, c, i+1, cx, cy+1, cz, sx, sy+c[i], sz);
    if (cz < n) dfs(C, c, i+1, cx, cy, cz+1, sx, sy, sz+c[i]);
};

const int M = 3013; 
int bit[M+1][M+1];

inline void add(int x, int _y, int val) {
    for (; x <= M; x += (x&-x)) {
        for (int y=_y; y <= M; y += (y&-y)) {
            bit[x][y] += val;
        }
    }
}
inline int query(int x, int _y) {
    int tmp = 0;
    for (; x > 0; x -= (x&-x)) {
        for (int y=_y; y > 0; y -= (y&-y)) {
            tmp += bit[x][y];
        }
    }
    return tmp;
}

// large TLE, may write global array constant-optimize work.
// use 2D-BIT, or can use 1d-BIT with sort(linear sweep)
void solve() {
    cin >> n;
    vector<int> a(3*n);
    vector<int> b(3*n);
    for (auto& x: a) {
        cin >> x;
    }
    for (auto& x: b) {
        cin >> x;
    }
    const int N = 756766; 
    vector<Node> A; A.reserve(N);
    vector<Node> B; B.reserve(N);
    dfs(A, a);
    dfs(B, b);
    vector<int> su; su.reserve(N);
    for (auto& p: B) {
        su.emplace_back(p.x);
    }
    sort(su.begin(), su.end());
    su.erase(unique(su.begin(), su.end()), su.end());
    unordered_map<int, int> map;
    for (int i = 0; i < su.size(); i++) {
        map[su[i]] = i+1;
    }
    vector<int> us; us.reserve(N);
    for (auto& p: A) {
        us.emplace_back(p.x);
    }
    sort(us.begin(), us.end());
    us.erase(unique(us.begin(), us.end()), us.end());
    unordered_map<int, int> aap;
    for (int i = 0; i < us.size(); i++) {
        int j = lower_bound(su.begin(), su.end(), us[i]) - su.begin();
        aap[us[i]] = j;
    }
    // <(x,y)
    memset(bit, 0, sizeof bit);
    for (auto& p: B) {
        add(map[p.x], map[p.y], 1);
    }
    for (auto& p: A) {
        p.s += query(aap[p.x], aap[p.y]);
    }
    // <(x,z)
    memset(bit, 0, sizeof bit);
    for (auto& p: B) {
        add(map[p.x], map[p.z], 1);
    }
    for (auto& p: A) {
        p.s += query(aap[p.x], aap[p.z]);
    }
    // <(y,z)
    memset(bit, 0, sizeof bit);
    for (auto& p: B) {
        add(map[p.y], map[p.z], 1);
    }
    for (auto& p: A) {
        p.s += query(aap[p.y], aap[p.z]);
    }
    // <(x,y,z), remove 2*
    sort(A.begin(), A.end(), [](auto& u, auto& v){
            return u.x < v.x;
            });
    sort(B.begin(), B.end(), [](auto& u, auto& v){
            return u.x < v.x;
            });
    memset(bit, 0, sizeof bit);
    int j = 0;
    int mxp = 0;
    for (auto& p: A) {
        while (j < B.size() && B[j].x < p.x) {
            add(map[B[j].y], map[B[j].z], 1);
            j++;
        }
        p.s -= 2 * query(aap[p.y], aap[p.z]);
        mxp = max(mxp, p.s);
    }
    long double res = (long double)mxp / B.size();
    cout << fixed << setprecision(8) << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
