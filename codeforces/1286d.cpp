#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353; // 998244853;

template <typename T>
struct modular {
    constexpr modular() : val(0){}
    constexpr modular(const modular<T>& _m) : val(_m.val) {}
    template <typename U> constexpr modular(const U& _r = U()) {
        val = -MOD <= _r && _r < MOD ? _r: _r % MOD;
        if (val < 0) { val += MOD; } }
    const T operator()() { return val; }
    template <typename U> explicit operator U() const { return static_cast<U>(val); }
    modular<T>& operator+=(const modular<T>& _m) { if ((val += _m.val) >= MOD) { val -= MOD; } return *this; }
    modular<T>& operator-=(const modular<T>& _m) { if ((val -= _m.val) < 0) { val += MOD; } return *this; }
    modular<T>& operator*=(const modular<T>& _m) { val = modular<T>(static_cast<int64_t>(val) * static_cast<int64_t>(_m.val)).val; return *this; }
    modular<T>& operator/=(const modular<T>& _m) {
        T a = _m.val, b = MOD, u = 0, v = 1;
        while (a != 0) {
            T q = b / a;
            b -= q * a; swap(a, b);
            u -= q * v; swap(u, v); 
        } return *this *= u; }
    modular<T>& operator =(const modular<T>& _m) { val = _m.val; return *this; }
    template <typename U> modular<T>& operator+=(const U& _r) { return *this += modular<T>(_r); }
    template <typename U> modular<T>& operator-=(const U& _r) { return *this -= modular<T>(_r); }
    template <typename U> modular<T>& operator*=(const U& _r) { return *this *= modular<T>(_r); }
    template <typename U> modular<T>& operator/=(const U& _r) { return *this /= modular<T>(_r); } 
    template <typename U> modular<T>& operator =(const U& _r) { val = modular<T>(_r).val; return *this; }
    modular<T> operator-() { return modular<T>(-val); }    
    template <typename U> friend bool operator==(const modular<U>&, const modular<U>&);
    friend std::istream& operator>>(std::istream& os, modular<T>& _m) { os >> _m.val; _m *= 1; return os; }
    friend std::ostream& operator<<(std::ostream& os, const modular<T>& _m) { return os << _m.val; }
    template <typename U>
    modular<T> exp(U e) {
        modular<T> res = 1;
        modular<T> b = val;
        if (e < 0) { b = 1/b; e *= -1; }
        for (; e; e >>= 1) {
            if (e & 1) { res *= b; }
            b *= b;
        } return res; }
private:
    T val;
};
template <typename T> inline modular<T> operator+(const modular<T>& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) += _rhs; }
template <typename T, typename U> inline modular<T> operator+(const modular<T>& _lhs, const U& _rhs) { return modular<T>(_lhs) += _rhs; }
template <typename T, typename U> inline modular<T> operator+(const U& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) += _rhs; }
template <typename T> inline modular<T> operator-(const modular<T>& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) -= _rhs; }
template <typename T, typename U> inline modular<T> operator-(const modular<T>& _lhs, const U& _rhs) { return modular<T>(_lhs) -= _rhs; }
template <typename T, typename U> inline modular<T> operator-(const U& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) -= _rhs; }
template <typename T> inline modular<T> operator*(const modular<T>& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) *= _rhs; }
template <typename T, typename U> inline modular<T> operator*(const modular<T>& _lhs, const U& _rhs) { return modular<T>(_lhs) *= _rhs; }
template <typename T, typename U> inline modular<T> operator*(const U& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) *= _rhs; }
template <typename T> inline modular<T> operator/(const modular<T>& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) /= _rhs; }
template <typename T, typename U> inline modular<T> operator/(const modular<T>& _lhs, const U& _rhs) { return modular<T>(_lhs) /= _rhs; }
template <typename T, typename U> inline modular<T> operator/(const U& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) /= _rhs; }
template <typename T> inline bool operator==(const modular<T>& _lhs, const modular<T>& _rhs) { return _lhs.val == _rhs.val; }
template <typename T, typename U> inline bool operator==(const modular<T>& _lhs, const U& _rhs) { return _lhs == modular<T>(_rhs); }
template <typename T, typename U> inline bool operator==(const U& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) == _rhs; }
template <typename T> inline bool operator!=(const modular<T>& _lhs, const modular<T>& _rhs) { return !(_lhs == _rhs); }
template <typename T, typename U> inline bool operator!=(const modular<T>& _lhs, const U& _rhs) { return !(_lhs == _rhs); }
template <typename T, typename U> inline bool operator!=(const U& _lhs, const modular<T>& _rhs) { return !(_lhs == _rhs); }
typedef modular<int> mint;

struct Matrix {
    mint a[2][2];
    Matrix() {a[0][0]=a[1][1]=1;}

    Matrix operator*(const Matrix& _m) const{
        Matrix r;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                r.a[i][j] = 0;
                for (int k = 0; k < 2; k++) {
                    r.a[i][j] += a[i][k] * _m.a[k][j];
                }
            }
        }
        return r;
    }
};

const int N = 100005; 
Matrix raw[N<<2];
template <typename T=int>
struct Segtree {
    int n; // leaf [n, 2n), view as original [0, n)
    int sz_v;
    //const T ID;
    vector<T> v; //tree
    
    Segtree(int _n = 100005) : n(_n), sz_v(n<<1){
        v.resize(sz_v);
    }
    void init() {// set leaf value
        for (int i = 0; i < n; i++) {
            v[i+n] = raw[i];
            //cout << i+n << ": ";
            //cout << v[i+n].a[0][0]<<'.';
            //cout << v[i+n].a[0][1]<<'.';
            //cout << v[i+n].a[1][0]<<'.';
            //cout << v[i+n].a[1][1]<<'.';
        }
        build();
    }
    // bug, when non-commutative, n should be 2^p,
    // e.g. n=3,
    //    1 2
    //   3 4 5, 2 is by(4,5)      
    //   then 1 is by(2,3), but it should be the order (3,2).
    void build() {
        for (int i = n-1; i > 0; i--) {
            v[i] = v[i<<1] * v[i<<1|1];
            //cout << i << ": ";
            //cout << v[i].a[0][0]<<'.';
            //cout << v[i].a[0][1]<<'.';
            //cout << v[i].a[1][0]<<'.';
            //cout << v[i].a[1][1]<<'.';
        }
    }
    inline void update(int p) {
        assert(p>=0);
        for (p += n; p >>= 1;) {
            v[p] = v[p<<1] * v[p<<1|1];
        }
    }
    inline mint query() {
        mint sum = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                sum += v[1].a[i][j];
                //cout << v[1].a[i][j] << "\n";
            }
        }
        return sum;
    }

};


typedef Segtree<Matrix> Seg;

struct Event {
    int dist, velo, i;
    int x,y;
    Event() {}
    Event(int _dist, int _velo, int _i, int _x, int _y) : dist(_dist), velo(_velo), i(_i), x(_x), y(_y) {}
    bool operator<(const Event& _oth) const {
        return 1ll*dist * _oth.velo < 1ll*_oth.dist * velo;
    }
};

// each proton state 2x2 matrix
// (<- 0 )  (<- ->)   (<- ->)
// (0  ->)  (<- ->)...(<- ->)
// when disable one event, let [i][x][y] = 0
void solve() {
    int n; cin >> n;
    mint i100 = mint(1)/100;
    vector<int> X(n), V(n);
    vector<mint> P(n);
    for (int i = 0; i < n; i++) {
        cin >> X[i] >> V[i] >> P[i];
        P[i] *= i100;
    }
    raw[0].a[0][0] = 1-P[0]; raw[0].a[0][1] = 0;
    raw[0].a[1][0] = 0; raw[0].a[1][1] =  P[0];
    vector<Event> es;
    for (int i = 1; i < n; i++) {
        raw[i].a[0][0] = 1-P[i]; raw[i].a[0][1] = P[i];
        raw[i].a[1][0] = 1-P[i]; raw[i].a[1][1] = P[i];

        int dx = X[i]-X[i-1];
        es.emplace_back(dx, V[i]+V[i-1], i, 1, 0);
        if (V[i] > V[i-1]) {
            es.emplace_back(dx, V[i]-V[i-1], i, 0, 0);
        }
        if (V[i] < V[i-1]) {
            es.emplace_back(dx, V[i-1]-V[i], i, 1, 1);
        }
    }
    sort(es.begin(), es.end());
    n = 1 << (32-__builtin_clz(n));
    Seg seg(n);
    seg.init();
    //seg.build(); twice??....noob
    mint prob = seg.query();
    //cout << prob << "\n";
    assert(prob == 1);
    mint res = 0;
    for (auto& e: es) {
        mint tim = e.dist / mint(e.velo);
        seg.v[e.i+n].a[e.x][e.y] = 0;
        seg.update(e.i);
        auto nxt = seg.query();
        mint hold = prob - nxt; prob = nxt;
        res += hold * tim;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
