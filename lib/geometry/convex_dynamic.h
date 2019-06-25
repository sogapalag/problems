
#include <bits/stdc++.h>

using namespace std;


// SNIPPETS_START convex_dynamic
using ll=long long;

const ll is_query = -(1ll<<62);
struct Line {
    ll k, b;
    Line() {}
    Line(const Line& _r) : k(_r.k), b(_r.b) {}
    Line(ll _k, ll _b) : k(_k), b(_b) {}

    inline ll eval(ll x) const{
        return k*x + b;
    }
    // act like point
    Line& operator-=(const Line& _r) {
        k -= _r.k; b -= _r.b;
        return *this;
    }
    friend Line operator-(const Line& _lhs, const Line& _rhs) {
        return Line(_lhs) -= _rhs;
    }
   // ll cross(const Line& _r) const{
   //     return k*_r.b - b*_r.k;
   // }
    // watch out whether overflow
    inline long double cross(const Line& _r) const{
        return (long double) k*_r.b - (long double) b*_r.k;
    }

    mutable function<const Line* ()> succ;
    
    bool operator < (const Line& _r) const{
        if (_r.b != is_query) return k < _r.k || (k==_r.k && b<_r.b);
        const Line* s = succ();
        if (!s) return false;
        return eval(_r.k) < s->eval(_r.k);
    }
};
struct Hull: public multiset<Line> {// max
    inline bool bad(iterator it) {
        auto z = next(it);
        if (z == end()) return false;
        if (it == begin()) {
            return it->k == z->k;
        }
        auto x = prev(it);
        return (*z - *it).cross(*it - *x) <= 0;
    }
    inline void add_line(ll k, ll b) {
        auto it = insert({k, b});
        if (bad(it)) { erase(it); return; }
        it->succ = [=] { return next(it)==end()? 0: &*next(it); };
        while (next(it) != end() && bad(next(it))) {
            erase(next(it));
        }
        while (it != begin() && bad(prev(it))) {
            erase(prev(it));
        }
    }
    inline ll query(ll x) {
        auto it = lower_bound((Line){x, is_query});
        return it->eval(x);
    }
};
// SNIPPETS_END
