#include <bits/stdc++.h>

using namespace std;

// make sure permutation is [0..=n-1]
struct Perm : vector<int> {
    using vector<int>::vector;
    Perm() {}
    Perm(initializer_list<int> list) : vector<int>(list) {}
    
};

Perm& operator*=(Perm& a, const Perm& b) {
    assert(a.size() == b.size());
    int n = a.size();
    Perm _a(a);
    for (int i = 0; i < n; i++) {
        a[i] = _a[b[i]];
    }
    return a;
}
Perm operator*(const Perm& a, const Perm& b) {
    assert(a.size() == b.size());
    int n = a.size();
    Perm c(n);
    for (int i = 0; i < n; i++) {
        c[i] = a[b[i]];
    }
    return c;
}

const int M = 120;
int m;
int hsh[M];
Perm P[M];
int id[65536];
int t[M][M];
int n, k;

int get_hsh(Perm& p){
    int res = 0;
    for (int i = 0; i < (int)p.size(); i++) {
        res |= p[i] << (i*3);
    }
    return res;
}
void prep(){
    Perm p(k);
    iota(p.begin(), p.end(), 0);
    m = 0;
    do {
        hsh[m] = get_hsh(p);
        id[hsh[m]] = m;
        P[m++] = p;
    }while(next_permutation(p.begin(), p.end()));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            auto p = P[i]*P[j];
            t[i][j] = id[get_hsh(p)];
        }
    }
}

using Bs = bitset<M>;
vector<int> gen;
void expand(Bs& b, int i) {
    if (b[i]) return;
    gen.emplace_back(i);
    queue<int> q;
    for (int j = 0; j < m; j++) {
        if (b[j]) q.push(j);
    }
    while (!q.empty()) {
        int j = q.front(); q.pop();
        for (int i: gen) {
            int x = t[i][j];
            if (!b[x]) {
                b[x] = 1;
                q.push(x);
            }
        }
    }
}

void solve() {
    cin >> n >> k;
    prep();

    vector<int> a(n);
    vector<int> las(m, -1);
    
    long long res = 0;
    for (int r = 0; r < n; r++) {
        Perm p(k);
        for (auto& x: p) {
            cin >> x; x--;
        }
        int i = id[get_hsh(p)];
        a[r] = i;
        las[i] = r;

        gen.clear();
        Bs b; b[0] = 1;
        vector<int> pos;
        for (int j = 0; j < m; j++) {
            if (las[j] != -1) pos.emplace_back(las[j]);
        }
        sort(pos.begin(), pos.end(), greater<int>());
        for (size_t _ = 0; _ < pos.size(); _++) {
            int l = pos[_];
            expand(b, a[l]);
            int len = _+1==pos.size()? l+1 : l - pos[_+1];
            res += b.count() * len;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
