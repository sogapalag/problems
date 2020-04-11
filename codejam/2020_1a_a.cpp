#include <bits/stdc++.h>

using namespace std;

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

// as long as prefix/suffix valid
//  *[]*[]*[]*, can treat [][][], and each string just s1s2s3 is fine
// exception for has full, greedy check match middle
// so messy, any elegant?
//
// read problem carefully, AT LEAST ONE, no full case.....
void solve() {
    int n; cin >> n;
    vector<string> s(n);
    bool full = false;
    string F;
    bool invalid = false;
    vector<bool> trk(n);  int id = 0;
    for (auto& x: s) {
        cin >> x;
        for (char c:x) {
            if (c=='*') goto nxt;
        }
        if (full) {
            if (F != x) {
                invalid = true;
                //cout << "*\n"; return;
            }
        } else {
            full = true;
            F = x;
        }
        trk[id] = true;
        nxt:;
        id++;
    }
    if (invalid) {
        cout << "*\n"; return;
    }
    if (full) {
        for (int i = 0; i < n; i++) {
            if (!trk[i]) {
                int k, m = s[i].size();
                for (k = 0; k < m; k++) {
                    if (s[i][k] == '*') break;
                }
                string pref = s[i].substr(0, k);
                k = m-1;
                for (; k>=0;k--){
                    if (s[i][k] == '*') break;
                }
                string suff = s[i].substr(k+1, m-(k+1));
dbg(pref, suff);
                if (pref.size() + suff.size() > F.size()) {
        cout << "*\n"; return;
                }
                for (int k = 0; k < (int)pref.size(); k++) {
                    if (pref[k] != F[k]) {
        cout << "*\n"; return;
                    }
                }
                for (int k = 0; k < (int)suff.size(); k++) {
                    if (suff[suff.size() - k - 1] != F[F.size() - k - 1]) {
        cout << "*\n"; return;
                    }
                }
                auto T = F.substr(pref.size(), F.size()-pref.size()-suff.size());
                int ii = 0, mm = T.size();
                vector<int> cut;
                for (int k = 0; k < m; k++) {
                    if (s[i][k] == '*') cut.push_back(k);
                }
                for (int _ = 1; _ < (int)cut.size(); _++) {
                    int l = cut[_-1]+1;
                    int r = cut[_];
                    if (l==r) continue;
                    auto t = s[i].substr(l, r-l);
                    while (ii + r-l <= mm && t != T.substr(ii, r-l)) {
                        ++ii;
                    }
                    ii += r-l;
                    if (ii > mm) {
        cout << "*\n"; return;
                    }
                }
            }
        }
        cout << F << '\n'; return; 
    }

    vector<vector<int>> cuts(n);
    int pp=0, ss=0;
    string P,S; 
    for (int i = 0; i < n; i++) {
        int m = s[i].size();
        for (int k = 0; k < m; k++) {
            if (s[i][k] == '*') cuts[i].push_back(k);
        }
        auto& cut = cuts[i];
        if (cut[0] > pp) {
            pp = cut[0];
            P = s[i].substr(0, pp);
        }
        if (m-1 - cut.back() > ss) {
            ss = m-1 - cut.back();
            S = s[i].substr(cut.back()+1, ss);
        }
    }
    string mid;
    for (int i = 0; i < n; i++) {
        auto& cut = cuts[i];
        auto pref = s[i].substr(0, cut[0]);
        auto suff = s[i].substr(cut.back()+1, s[i].size() - 1-cut.back());
        for (int k = 0; k < (int)pref.size(); k++) {
            if (pref[k] != P[k]) {
cout << "*\n"; return;
            }
        }
        for (int k = 0; k < (int)suff.size(); k++) {
            if (suff[suff.size() - k - 1] != S[S.size() - k - 1]) {
cout << "*\n"; return;
            }
        }
        for (int k = cut[0]; k < cut.back(); k++) {
            if (s[i][k] != '*') mid.push_back(s[i][k]);
        }
    }
    cout << P << mid << S << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
