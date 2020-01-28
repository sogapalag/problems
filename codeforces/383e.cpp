#include <bits/stdc++.h>

using namespace std;

// in theoretical term, Z/M may called mobius transform/inversion on subset lattice
// O(n 2^n) Yates
#define __loop(f) \
    for (int i = 0, n = 31-__builtin_clz((int)f.size()), MSK = 1<<n; i < n; i++)\
        for (int msk = 0; msk < MSK; msk++)\
            if (msk>>i&1)

// F=Z(f). F[X] := sum_{S sub X} f[S]
template <typename T>
inline void fast_subset_zeta_transform(vector<T>& f) {
    __loop(f) f[msk] += f[msk ^ 1<<i];
}
// F=M(f). F[X] := sum_{S sub X} (-1)^|X\S| f[S]. 
// MZ = ZM = I
template <typename T>
inline void fast_subset_mobius_transform(vector<T>& f) {
    __loop(f) f[msk] -= f[msk ^ 1<<i];
}
// F=Z'(f). F[X] := sum_{X sub S} f[S]
// Z' = rZr. Z = rZ'r
template <typename T>
inline void fast_superset_zeta_transform(vector<T>& f) {
    __loop(f) f[msk ^ 1<<i] += f[msk];
}
// F=r(f). F[X] := f[W\X]
template <typename T>
inline void map_complement(vector<T>& f) {
    reverse(f.begin(), f.end());
}
// F=M'(f). F[X] := sum_{X sub S} (-1)^|S\X| f[S]
// M'Z' = Z'M' = I.
// M' = rMr.  M = rM'r
template <typename T>
inline void fast_superset_mobius_transform(vector<T>& f) {
    __loop(f) f[msk ^ 1<<i] -= f[msk];
}
using ll=long long;
// cnt[3] would MLE, but idea much clear.
void __solve() {
    int n; cin >> n;
    const int MSK = 1<<24; 
    //vector<vector<int>> cnt(3, vector<int>(MSK));
    vector<int> cnt(MSK);
    for (int _ = 0; _ < n; _++) {
        string s; cin >> s;
        // dump write, just iter sub
        sort(s.begin(), s.end());
        s.erase(unique(s.begin(), s.end()), s.end());
        //for (char c:s) cnt[0][1<<(c-'a')]++;
        for (char c:s) cnt[1<<(c-'a')]++;
        if (s.size() >= 2) {
            int x = s[0]-'a';
            int y = s[1]-'a';
            //cnt[1][1<<x | 1<<y]++;
            cnt[1<<x | 1<<y]--;
            if (s.size() >= 3) {
                int z = s[2]-'a';
                //cnt[1][1<<x | 1<<z]++;
                //cnt[1][1<<y | 1<<z]++;
                //cnt[2][1<<x | 1<<y | 1<<z]++;
                cnt[1<<x | 1<<z]--;
                cnt[1<<y | 1<<z]--;
                cnt[1<<x | 1<<y | 1<<z]++;
            }
        }
    }
    //for (int i = 0; i < 3; i++) {
    //    fast_subset_zeta_transform(cnt[i]);
    //}
    fast_subset_zeta_transform(cnt);
    ll res = 0;
    for (int msk = 0; msk < MSK; msk++) {
        //ll tmp = 0;
        //for (int i = 0; i < 3; i++) {
        //    tmp += ((i&1)?-1:1) * cnt[i][msk];
        //}
        ll tmp = cnt[msk];
        res ^= tmp*tmp;
    }
    cout << res;
}

// for fix vowels, consider IEP, that I_i = [v_i setted]
//   then cap(I_J) would contribute to msk s.t. J sub msk, i.e. we do a zeta.
void solve() {
    int n; cin >> n; // 1e4, no need ll
    const int MSK = 1<<24; 
    vector<int> cnt(MSK);
    for (int _ = 0; _ < n; _++) {
        string s; cin >> s;
        int msk = 0;
        for (char c:s) msk |= 1<<(c-'a');
        for (int sub = msk; sub >= 1; (sub-=1)&=msk) {
            int x = (__builtin_popcount(sub)&1) ? 1 : -1;
            cnt[sub] += x;
        }
    }
    fast_subset_zeta_transform(cnt);
    int res = 0;
    for (int x: cnt) res ^= x*x;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
