#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START modular_var
int MOD[] = {1000000007, 998244353, 998244853};

template <int ITH>
struct modular {
    constexpr modular() : val(0){}
    constexpr modular(const modular& _m) : val(_m.val) {}
    template <typename U> constexpr modular(const U& _r = U()) {
        val = -MOD[ITH] <= _r && _r < MOD[ITH] ? _r: _r % MOD[ITH];
        if (val < 0) { val += MOD[ITH]; } }
    const int operator()() { return val; }
    template <typename U> explicit operator U() const { return static_cast<U>(val); }
    modular& operator+=(const modular& _m) { if ((val += _m.val) >= MOD[ITH]) { val -= MOD[ITH]; } return *this; }
    modular& operator-=(const modular& _m) { if ((val -= _m.val) < 0) { val += MOD[ITH]; } return *this; }
    modular& operator*=(const modular& _m) { val = modular(static_cast<int64_t>(val) * static_cast<int64_t>(_m.val)).val; return *this; }
    modular& operator/=(const modular& _m) {
        int a = _m.val, b = MOD[ITH], u = 0, v = 1;
        while (a != 0) {
            int q = b / a;
            b -= q * a; swap(a, b);
            u -= q * v; swap(u, v); 
        } return *this *= u; }
    modular& operator =(const modular& _m) { val = _m.val; return *this; }
    template <typename U> modular& operator+=(const U& _r) { return *this += modular(_r); }
    template <typename U> modular& operator-=(const U& _r) { return *this -= modular(_r); }
    template <typename U> modular& operator*=(const U& _r) { return *this *= modular(_r); }
    template <typename U> modular& operator/=(const U& _r) { return *this /= modular(_r); } 
    template <typename U> modular& operator =(const U& _r) { val = modular(_r).val; return *this; }
    modular operator-() { return modular(-val); }    
    template <typename U> friend bool operator==(const modular&, const modular&);
    friend std::istream& operator>>(std::istream& os, modular& _m) { os >> _m.val; _m *= 1; return os; }
    friend std::ostream& operator<<(std::ostream& os, const modular& _m) { return os << _m.val; }
    template <typename U>
    modular exp(U e) {
        modular res = 1;
        modular b = val;
        if (e < 0) { b = 1/b; e *= -1; }
        for (; e; e >>= 1) {
            if (e & 1) { res *= b; }
            b *= b;
        } return res; }
private:
    int val;
};
template <int ITH> inline modular<ITH> operator+(const modular<ITH>& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) += _rhs; }
template <int ITH, typename U> inline modular<ITH> operator+(const modular<ITH>& _lhs, const U& _rhs) { return modular<ITH>(_lhs) += _rhs; }
template <int ITH, typename U> inline modular<ITH> operator+(const U& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) += _rhs; }
template <int ITH> inline modular<ITH> operator-(const modular<ITH>& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) -= _rhs; }
template <int ITH, typename U> inline modular<ITH> operator-(const modular<ITH>& _lhs, const U& _rhs) { return modular<ITH>(_lhs) -= _rhs; }
template <int ITH, typename U> inline modular<ITH> operator-(const U& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) -= _rhs; }
template <int ITH> inline modular<ITH> operator*(const modular<ITH>& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) *= _rhs; }
template <int ITH, typename U> inline modular<ITH> operator*(const modular<ITH>& _lhs, const U& _rhs) { return modular<ITH>(_lhs) *= _rhs; }
template <int ITH, typename U> inline modular<ITH> operator*(const U& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) *= _rhs; }
template <int ITH> inline modular<ITH> operator/(const modular<ITH>& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) /= _rhs; }
template <int ITH, typename U> inline modular<ITH> operator/(const modular<ITH>& _lhs, const U& _rhs) { return modular<ITH>(_lhs) /= _rhs; }
template <int ITH, typename U> inline modular<ITH> operator/(const U& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) /= _rhs; }
template<int ITH> inline bool operator==(const modular<ITH>& _lhs, const modular<ITH>& _rhs) { return _lhs.val == _rhs.val; }
template <int ITH, typename U> inline bool operator==(const modular<ITH>& _lhs, const U& _rhs) { return _lhs == modular<ITH>(_rhs); }
template <int ITH, typename U> inline bool operator==(const U& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) == _rhs; }
template <int ITH> inline bool operator!=(const modular<ITH>& _lhs, const modular<ITH>& _rhs) { return !(_lhs == _rhs); }
template <int ITH, typename U> inline bool operator!=(const modular<ITH>& _lhs, const U& _rhs) { return !(_lhs == _rhs); }
template <int ITH, typename U> inline bool operator!=(const U& _lhs, const modular<ITH>& _rhs) { return !(_lhs == _rhs); }
typedef modular<0> mint;
// SNIPPETS_END
