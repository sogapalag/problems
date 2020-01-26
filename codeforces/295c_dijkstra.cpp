#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007; // 998244353; // 998244853; 

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

const int INF = 0x3f3f3f3f;
int n,k;
int a=0,b=0;

const int N = 55; 
mint c[N][N];
void prep() {
    c[0][0] = 1;
    for (int i = 1; i < N; i++) {
        c[i][0] = 1;
        for (int j = 1; j < N; j++) {
            c[i][j] = c[i-1][j-1] + c[i-1][j];
        }
    }
}

int dis[2][N][N];
mint way[2][N][N];
bool trk[2][N][N];
struct Dijk {
    int dis;
    int x, y, z;
    Dijk() {}
    Dijk(int _dis, int _x, int _y, int _z) : dis(_dis), x(_x), y(_y), z(_z) {}
    bool operator<(const Dijk& _oth) const {
        return dis > _oth.dis;
    }
};

// state [boat-pos][b1][b2]
void solve() {
    prep();
    cin >> n >> k; k/=50;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        assert(x==50||x==100);
        x==50? a++ : b++;
    }

    memset(dis, INF, sizeof dis);
    dis[0][a][b] = 0; way[0][a][b] = 1;
    priority_queue<Dijk> pq;
    pq.push({0,0,a,b});
    while (!pq.empty()) {
        int d, x,y,z;
        auto& _ =pq.top();
        d=_.dis,x=_.x,y=_.y,z=_.z; pq.pop();
        if (trk[x][y][z] || d > dis[x][y][z]) continue;
        trk[x][y][z] = 1;
        for (int i = 0; i <= y; i++) {
            for (int j = 0; j <= z && i+2*j <= k; j++) {
                if (i||j) {
                    int u = x^1;
                    int v = a-(y-i);
                    int w = b-(z-j);
                    int new_dis = dis[x][y][z] + 1;
                    mint new_way = way[x][y][z] * c[y][i] * c[z][j];
                    if (dis[u][v][w] > new_dis) {
                        dis[u][v][w] = new_dis;
                        way[u][v][w] = new_way;
                        pq.push({new_dis, u,v,w});
                    } else if (dis[u][v][w] == new_dis) {
                        way[u][v][w] += new_way;
                    }
                }
            }
        }
    }

    int ride = dis[1][a][b];
    mint res = way[1][a][b];
    if (ride < INF) {
        cout << ride << '\n' << res;
    } else {
        cout << "-1\n0";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
