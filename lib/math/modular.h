#include <bits/stdc++.h>

using namespace std;
//~ SNIPPETS_START modular
namespace math {
    const int MOD = 1000000007; // 998244353
    
    template <typename T>
    struct modular {
        constexpr modular() : val(0){}
        constexpr modular(const modular<T>& _m) : val(_m.val) {}
        template <typename U>
        constexpr modular(const U& _r = U()) {
            val = -MOD <= _r && _r < MOD ? _r: _r % MOD;
            if (val < 0) { val += MOD; }
        }
        const T operator()() { return val; }
        template <typename U>
        explicit operator U() const { return static_cast<U>(val); }
        
        // arithmetic
        modular<T>& operator+=(const modular<T>&);
        template <typename U>
        modular<T>& operator+=(const U&);
        modular<T>& operator-=(const modular<T>&);
        template <typename U>
        modular<T>& operator-=(const U&);
        modular<T>& operator*=(const modular<T>&);
        template <typename U>
        modular<T>& operator*=(const U&);
        modular<T>& operator/=(const modular<T>&);
        template <typename U>
        modular<T>& operator/=(const U&);
        
        modular<T>& operator=(const modular<T>& _m) { val = _m.val; return *this; }
        template <typename U>
        modular<T>& operator=(const U& _r) { val = modular<T>(_r).val; return *this; }
        modular<T> operator-() { return modular<T>(-val); }
        
        template <typename U>
        friend bool operator==(const modular<U>&, const modular<U>&);
        // I/O
        friend std::istream& operator>>(std::istream& os, modular<T>& _m) {
            os >> _m.val; _m *= 1;
            return os;
        }
        friend std::ostream& operator<<(std::ostream& os, const modular<T>& _m) {
            return os << _m.val;
        }

        template <typename U>
        modular<T> exp(U e) {
            modular<T> res = 1;
            modular<T> b = val;
            if (e < 0) { b = 1/b; e *= -1; }
            for (; e; e >>= 1) {
                if (e & 1) { res *= b; }
                b *= b;
            }
            return res;
        }
    private:
        T val;
    };
    // AddAssign
    template <typename T>
    modular<T>&
    modular<T>::operator+=(const modular<T>& _m) {
        if ((val += _m.val) >= MOD) { val -= MOD; }
        return *this;
    }
    template <typename T>
    template <typename U>
    modular<T>& 
    modular<T>::operator+=(const U& _r) { return *this += modular<T>(_r); }
    // SubAssign
    template <typename T>
    modular<T>& 
    modular<T>::operator-=(const modular<T>& _m) {
        if ((val -= _m.val) < 0) { val += MOD; }
        return *this;
    }
    template <typename T>
    template <typename U>
    modular<T>& 
    modular<T>::operator-=(const U& _r) { return *this -= modular<T>(_r); }
    // MultAssign
    template <typename T>
    modular<T>& 
    modular<T>::operator*=(const modular<T>& _m) {
        val = modular<T>(static_cast<int64_t>(val) * static_cast<int64_t>(_m.val)).val;
        return *this;
    }
    template <typename T>
    template <typename U>
    modular<T>& 
    modular<T>::operator*=(const U& _r) { return *this *= modular<T>(_r); }
    // DivAssign
    template <typename T>
    modular<T>& 
    modular<T>::operator/=(const modular<T>& _m) {
        T a = _m.val, b = MOD, u = 0, v = 1;
        while (a != 0) {
            T q = b / a;
            b -= q * a; swap(a, b);
            u -= q * v; swap(u, v); 
        }
        return *this *= u;
    }
    template <typename T>
    template <typename U>
    modular<T>& 
    modular<T>::operator/=(const U& _r) { return *this /= modular<T>(_r); }
    // Add
    template <typename T>
    inline modular<T>
    operator+(const modular<T>& _lhs, const modular<T>& _rhs) {
        return modular<T>(_lhs) += _rhs;
    }
    template <typename T, typename U>
    inline modular<T>
    operator+(const modular<T>& _lhs, const U& _rhs) {
        return modular<T>(_lhs) += _rhs;
    }
    template <typename T, typename U>
    inline modular<T>
    operator+(const U& _lhs, const modular<T>& _rhs) {
        return modular<T>(_lhs) += _rhs;
    }
    // Sub
    template <typename T>
    inline modular<T>
    operator-(const modular<T>& _lhs, const modular<T>& _rhs) {
        return modular<T>(_lhs) -= _rhs;
    }
    template <typename T, typename U>
    inline modular<T>
    operator-(const modular<T>& _lhs, const U& _rhs) {
        return modular<T>(_lhs) -= _rhs;
    }
    template <typename T, typename U>
    inline modular<T>
    operator-(const U& _lhs, const modular<T>& _rhs) {
        return modular<T>(_lhs) -= _rhs;
    }
    // Mult
    template <typename T>
    inline modular<T>
    operator*(const modular<T>& _lhs, const modular<T>& _rhs) {
        return modular<T>(_lhs) *= _rhs;
    }
    template <typename T, typename U>
    inline modular<T>
    operator*(const modular<T>& _lhs, const U& _rhs) {
        return modular<T>(_lhs) *= _rhs;
    }
    template <typename T, typename U>
    inline modular<T>
    operator*(const U& _lhs, const modular<T>& _rhs) {
        return modular<T>(_lhs) *= _rhs;
    }
    // Div
    template <typename T>
    inline modular<T>
    operator/(const modular<T>& _lhs, const modular<T>& _rhs) {
        return modular<T>(_lhs) /= _rhs;
    }
    template <typename T, typename U>
    inline modular<T>
    operator/(const modular<T>& _lhs, const U& _rhs) {
        return modular<T>(_lhs) /= _rhs;
    }
    template <typename T, typename U>
    inline modular<T>
    operator/(const U& _lhs, const modular<T>& _rhs) {
        return modular<T>(_lhs) /= _rhs;
    }
    // eq
    template <typename T>
    inline bool
    operator==(const modular<T>& _lhs, const modular<T>& _rhs) {
        return _lhs.val == _rhs.val;
    }
    template <typename T, typename U>
    inline bool
    operator==(const modular<T>& _lhs, const U& _rhs) {
        return _lhs == modular<T>(_rhs);
    }
    template <typename T, typename U>
    inline bool
    operator==(const U& _lhs, const modular<T>& _rhs) {
        return modular<T>(_lhs) == _rhs;
    }
    // neq
    template <typename T>
    inline bool
    operator!=(const modular<T>& _lhs, const modular<T>& _rhs) {
        return !(_lhs == _rhs);
    }
    template <typename T, typename U>
    inline bool
    operator!=(const modular<T>& _lhs, const U& _rhs) {
        return !(_lhs == _rhs);
    }
    template <typename T, typename U>
    inline bool
    operator!=(const U& _lhs, const modular<T>& _rhs) {
        return !(_lhs == _rhs);
    }
}
using namespace math;
typedef modular<int> mint;
//~ SNIPPETS_END
