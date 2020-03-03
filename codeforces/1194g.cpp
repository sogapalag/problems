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

#define LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(bool x) { return (x ? "T" : "F"); }
string to_string(const char* s) { return to_string((string)s); }
template <typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename V>
string to_string(V v) {
    bool f = true; string res = "[";
    for (const auto& x: v) {
        if (!f) res += ", ";
        f = false;
        res += to_string(x); } res += "]";
    return res;
}
void debug() { cerr << endl; }
template <typename H, typename... T>
void debug(H h, T... t) { cerr << " " << to_string(h); debug(t...); }
#ifdef LOCAL
#define dbg(args...) cerr<<"("<<#args<<") =", debug(args)
#else
#define dbg(args...) 2020
#endif

#define rep(i,n) for (int i=0;i<n;i++)

mint dp[2][2][2][9][9][16][16];
int px[10], py[10];
// process from least, let's call suffix
// gx, till now, suffix is larger(1) or <=(0) 
// cx, carry from past
// mx, msk indicate whether dx=x,2*x,3*x,4*x occured.
void solve() {
    string s; cin >> s;
    mint eq11 = 0;
    for (char x:s) eq11 = eq11*10 + (x-'0');
    reverse(s.begin(), s.end());

    mint res = 0;
    for (int x = 1; x <= 9; x++) {
        for (int y = 1; y < x; y++) {
    //{{ int x = 2, y = 1;
            if (__gcd(x,y) != 1) continue;
            memset(dp, 0, sizeof dp);
            dp[0][0][0][0][0][0][0] = 1;
            int crt = 0;
            const int MSK = 1<<(9/x); 
            const int LIM = 9/x; 
            for (char _:s) {
                int d = _-'0';
                int nxt = crt^1;
                memset(dp[nxt], 0, sizeof dp[nxt]);
                rep(gx,2)rep(gy,2)rep(cx,9)rep(cy,9)rep(mx,MSK)rep(my,MSK){
                    rep(z, 10){
                        int sx = x*z + cx;
                        int sy = y*z + cy;
                        int dx = sx%10, ncx = sx/10;
                        int dy = sy%10, ncy = sy/10;
                        int ngx = (dx == d ? gx : dx > d);
                        int ngy = (dy == d ? gy : dy > d);
                        int nmx = mx;
                        int nmy = my;
                        // watch out overflow
                        if (dx && dx % x == 0 && dx/x <= LIM) nmx |= 1<<(dx/x - 1); 
                        if (dy && dy % y == 0 && dy/y <= LIM) nmy |= 1<<(dy/y - 1);
                        dp[nxt][ngx][ngy][ncx][ncy][nmx][nmy] += dp[crt][gx][gy][cx][cy][mx][my];
                        //{
                        //    mint tmp = dp[nxt][ngx][ngy][ncx][ncy][nmx][nmy];
                        //    if (nmx==3&&nmy==1&&tmp!=0) {
                        //        //dbg(d,gx,gy,cx,cy,mx,my,z);
                        //        // 4 0 1 1 0 3 0 1
                        //    }
                        //}
                        //{
                        //    mint tmp = dp[nxt][0][1][1][0][3][0];
                        //    if (tmp != 0) {
                        //        dbg(d,gx,gy,cx,cy,mx,my,z);
                        //        dbg(ngx,ngy,ncx,ncy,nmx,nmy); // nmy=32?
                        //        dbg(dx,x,mx,nmx);
                        //        dbg(dy,y,mx,nmy); // 6 1 0 32.... // should limit... overflow
                        //        exit(0);
                        //    }
                        //}
                    }
                }
                crt ^= 1;
            }
            rep(mx,MSK)rep(my,MSK)if(mx&my){
                res += dp[crt][0][0][0][0][mx][my];
                //{
                //    mint v = dp[crt][0][0][0][0][mx][my];
                //    if (v!=0) cerr<<mx<<' '<<my<<' '<<v<<endl;
                //}
            }
            //cerr<<x<<' '<<y<<' '<<res<<endl;
        }
    }
    res = res*2 + eq11;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
