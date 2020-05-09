#include <bits/stdc++.h>

using namespace std;
using u128 = __uint128_t;

using ll=unsigned long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// Rolling Hash
struct RHash {
    //const ll R = 843823891, iR = 1040004855;
    //const ll M = 1637348371;
    //const ll R = 11, iR = 14007867;
    //const ll R = 17, iR = 4531957;
    //const ll M = 19260817;
    const ll R = 11, iR = 1257732550480196738;
    const ll M = (1ll<<62) + 135;
    vector<ll> a;
    vector<ll> pw;
    vector<ll> ipw;

    RHash() {
        assert(mul(R, iR) == 1);
        a.resize(256);
        iota(a.begin(), a.end(), 42);
        //for (auto& x: a) {
        //    x = rng()%R;
        //    (x+=R)%=R;
        //}
        const int N = 10'000'007;
        pw.resize(N); ipw.resize(N);
        pw[0] = 1; ipw[0] = 1;
        for (int i = 1; i < N; i++) {
            pw[i] = mul(pw[i-1], R);
            ipw[i] = mul(ipw[i-1], iR);
        }
    }

    inline ll add(ll x, ll y) {
        x += y; if (x > M) x-=M;
        return x;
        //return (x+y) %M;
    }
    inline ll sub(ll x, ll y) {
        return x<y? x+M-y : x-y;
        //return (x + M-y) %M;
    }
    inline ll mul(ll x, ll y) {
        return ((u128)x*y) %M;
    }

    vector<ll> get_hash(const string& s) {
        int n = s.size();
        vector<ll> sum(n+1);
        sum[0] = 0;
        for (int i = 0; i < n; i++) {
            sum[i+1] = add(sum[i], mul(pw[i], a[s[i]]));
        }
        return sum;
    }
    // s[l..r)
    ll get_sub(const vector<ll>& sum, int l, int r) {
        return mul(sub(sum[r], sum[l]), ipw[l]);
    }
}rh;
const int N = 2e5+10; 
const int L = 50; 
int n,q;
char a[N];
int pre[N], nxt[N];
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
// score. 72/100
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
gp_hash_table<ll, int, custom_hash> cnt;
//unordered_map<ll, int> cnt;

// ArrayList, not quite well, might need differ-impl
//const int B = 25; 
//const int MSK = 1<<B; 
//const int MSK1 = MSK-1; 
//vector<pair<ll,int>> Cnt[MSK];

void merge(int i, int j) {
    string s;
    int len = 0;
    nxt[i] = j; pre[j] = i;
    while (len < L-1 && i) {
        s.push_back(a[i]); ++len;
        i = pre[i];
    }
    reverse(s.begin(), s.end());
    int m = len; len = 0;
    while (len < L-1 && j) {
        s.push_back(a[j]); ++len;
        j = nxt[j];
    }
    len += m;
    auto sum = rh.get_hash(s);
    for (int i = 0; i < m; i++) {
        for (int j = m; j < len && j-i < L; j++) {
            ll h = rh.get_sub(sum, i, j+1);
            ++cnt[h];
            //for (auto& p: Cnt[h&MSK1]) {
            //    if ((h>>B)==p.first) {
            //        ++p.second; goto found;
            //    }
            //}
            //Cnt[h&MSK1].emplace_back(h>>B, 1);
            //found:;
        }
    }
}
void split(int i) {
    string s; int j = nxt[i];
    nxt[i] = pre[j] = 0;
    int len = 0;
    while (len < L-1 && i) {
        s.push_back(a[i]); ++len;
        i = pre[i];
    }
    reverse(s.begin(), s.end());
    int m = len; len = 0;
    while (len < L-1 && j) {
        s.push_back(a[j]); ++len;
        j = nxt[j];
    }
    len += m;
    auto sum = rh.get_hash(s);
    for (int i = 0; i < m; i++) {
        for (int j = m; j < len && j-i < L; j++) {
            ll h = rh.get_sub(sum, i, j+1);
            --cnt[h];
            //for (auto& p: Cnt[h&MSK1]) {
            //    if ((h>>B)==p.first) {
            //        --p.second; goto found_;
            //    }
            //}
            //Cnt[h&MSK1].emplace_back(h>>B, 1);
            //found_:;
        }
    }
}
const int MOD = 998244353; 

// birthday collision, require M > |X|^2 
// TODO need constant-optim. might use small M hash, many online codes just use overflowed sum, then to arraylist sum%M
void solve() {
    //cnt.reserve(2e8);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ++cnt[rh.a[a[i]]];
    }
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int i,j;
            cin >> i >> j;
            merge(i, j);
        } else if (op == 2) {
            int i; cin >> i;
            split(i);
        } else {
            string s; int k;
            cin >> s >> k;
            auto sum = rh.get_hash(s);
            int len = s.size();
            ll res = 1;
            for (int i = 0; i+k <= len; i++) {
                ll h = rh.get_sub(sum, i, i+k);
                if (cnt.find(h) == cnt.end()) {
                    res = 0; break;
                }
                res *= cnt[h];
                res %= MOD;
                //for (auto& p: Cnt[h&MSK1]) {
                //    if ((h>>B)==p.first) {
                //        res *= p.second;
                //        res %= MOD;
                //        goto found__;
                //    }
                //}
                //res = 0; break;
                //found__:;
            }
            cout << res << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
