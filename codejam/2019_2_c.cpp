#include <bits/stdc++.h>

using namespace std;
#define int long long
// some code copied from EBAIT from snackdown 2019 elimination round
struct Fraction {
  int p, q;
  bool operator<(const Fraction& other) const {
    return p * other.q < q * other.p;
  }

  vector<int> GetCC() const {
    int s = p / q;
    Fraction f{q, p - s * q};
    if (f.q == 0) { return {s}; }
    vector<int> other_cc = f.GetCC();
    other_cc.insert(other_cc.begin(), s);
    return other_cc;
  }

  static Fraction FromCC(vector<int> cc) {
    reverse(cc.begin(), cc.end());
    Fraction f{0, 1};

    bool is_first = true;
    for (int x : cc) {
      if (is_first) {
        is_first = false;
      } else {
        f = Fraction{f.q, f.p};
      }

      f.p += f.q * x;
    }

    assert(f.p <= 2e18 && f.q <= 2e18);
    return f;
  }
};

Fraction Approximate(Fraction lbound, Fraction rbound) {
  vector<int> lbound_cc = lbound.GetCC();
  vector<int> rbound_cc = rbound.GetCC();
  assert(count(lbound_cc.begin() + 1, lbound_cc.end(), 0) == 0);
  assert(count(rbound_cc.begin() + 1, rbound_cc.end(), 0) == 0);

  for (auto add_l : {false, true}) {
    for (auto add_r : {false, true}) {
      vector<int> lcc = lbound_cc;
      vector<int> rcc = rbound_cc;
      if (add_l) { --lcc.back(); lcc.push_back(1); }
      if (add_r) { --rcc.back(); rcc.push_back(1); }
      vector<int> res_cc;
      int ptr = 0;
      while (ptr < lcc.size() && ptr < rcc.size() && lcc[ptr] == rcc[ptr]) {
        res_cc.push_back(lcc[ptr]);
        ++ptr;
      }
      int min_val = 2e9;
      if (ptr < lcc.size()) { min_val = min(min_val, lcc[ptr]); }
      if (ptr < rcc.size()) { min_val = min(min_val, rcc[ptr]); }
      assert(min_val < 1.5e9);

      res_cc.push_back(min_val + 1);
      auto best_frac = Fraction::FromCC(res_cc);

      if (lbound < best_frac && best_frac < rbound) {
        return best_frac;
      }
    }
  }
  assert(false);
}
#undef LOCAL
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

// https://en.wikipedia.org/wiki/Continued_fraction#Best_rational_within_an_interval
// https://en.wikipedia.org/wiki/Stern%E2%80%93Brocot_tree
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        a[i] = {x,y};
    }
    Fraction l {0,1};
    Fraction r {(int)2e9, 1};
    for (int i = 1; i < n; i++) {
        int x,y;
        tie(x,y)=a[i];
        int u,v;
        tie(u,v)=a[i-1];
        int dx = x-u;
        int dy = y-v;
        if (dx<=0 && dy<=0) goto fail;
        if (dx*1ll*dy<0) {
            Fraction f{abs(dy), abs(dx)};
            dbg(f.p,f.q);
            if (dx < 0) {
                r = min(r, f);
            } else {
                l = max(l, f);
            }
            dbg(l.p,l.q);
            dbg(r.p,r.q);
        }
    }
    dbg(l.p,l.q,r.p,r.q);
    if (!(l < r)) goto fail;
    else {
        auto res = Approximate(l, r);
        cout << res.p << ' ' << res.q << '\n'; return;
    }
fail:;
    cout << "IMPOSSIBLE\n"; return;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
