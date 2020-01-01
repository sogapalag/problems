#include <bits/stdc++.h>

using namespace std;
using ull = uint64_t;
// fuck!! why write own stupid sub....unnessary&studpid................................
// just simple -
ull& sub(ull& r, const ull& x){
    if (r>=x) r-=x;
    //else r = x-r;
    else r = (~(x-r)) + 1;
    return r;
}
ull c2(ull n) { return n*(n-1)/2; }
//vector<int> g[1024];
#define int uint64_t
void solve() {
    int n,m;
    cin >> n >> m;
    ull A,B,C;
    cin >> A >> B >> C;
    vector<vector<int>> g(n);
    vector<ull> les(n), grt(n);
    vector<ull> sles(n), sgrt(n);
    vector<ull> pref(n), suff(n);
    for (int i = 1; i < n; i++) {
        pref[i] = pref[i-1] + i;
    }
    suff[n-1] = n-1;
    for (int i = n-1; i >= 1; i--) {
        suff[i-1] = suff[i] + i-1;
        assert(suff[i] == c2(n)-c2(i));
        if(suff[i] != c2(n)-c2(i)) {
            cerr << i << ' ' <<suff[i] <<' '<< (c2(n)-c2(i)) << endl; 
            exit(0);
        }
    }
    vector<pair<int, int>> es(m);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        if(x>y)swap(x,y);
        g[x].push_back(y);
        g[y].push_back(x);
        les[y]++; grt[x]++;
        sles[y] += x; sgrt[x] += y;
        es[_] = {x,y};
    }
    for (int i = 0; i < n; i++) {
        sort(g[i].begin(), g[i].end());
    }
    ull cnt[8]={};
    // 0
    {
        for (int i = 0; i+2 < n; i++) {
            cnt[0] += A*i * c2(n-i-1);
        }
        for (int j = 1; j+1 < n; j++) {
            cnt[0] += B*j * (j)*(n-j-1);
        }
        for (int k = 2; k < n; k++) {
            cnt[0] += C*k * c2(k);
        }
    }
    // i-j 0b001
    {
        for (auto& e: es) {
            int i,j;
            tie(i,j) = e;
            if(j==n-1)continue;
            cnt[1] += (A*i+B*j)*1ull * (n-j-1);
            //assert(suff[j+1] == c2(n)-c2(j+1));
            if (suff[j+1] != c2(n)-c2(j+1)) {
                cerr << j+1 << ' ' <<suff[j+1] <<' '<< (c2(n)-c2(j+1)) << endl; 
                exit(0);
            }
            cnt[1] += C*1ull*(c2(n)-c2(j+1));//suff[j+1];
        }
    }
    // j-k 0b010
    {
        for (auto& e: es) {
            int j,k;
            tie(j,k) = e;
            if(j==0)continue;
            cnt[2] += (B*j+C*k) *1ull* (j);
            cnt[2] += A* 1ull*c2(j); //pref[j-1];
        }
    }
    // i-k 0b100
    {
        for (auto& e: es) {
            int i,k;
            tie(i,k) = e;
            cnt[4] += (A*i+C*k) * 1ull *(k-i-1);
            cnt[4] += B*1ull*(c2(k)-c2(i+1)); //(pref[k-1] - pref[i]);
        }
    }
    // 011
    {
        for (int j = 1; j+1 < n; j++) {
            cnt[3] += A * 1ull * sles[j] * 1ull * grt[j];
            cnt[3] += les[j] * 1ull * C * 1ull * sgrt[j];
            cnt[3] += B * 1ull * j * 1ull * les[j] *1ull* grt[j];
        }
    }
    // 101
    {
        for (int i = 0; i+2 < n; i++) {
            ull x = 0;
            for (int j:g[i])if(j>i){
                x++;
                cnt[5] += B*j*1ull * (grt[i] - x);
                cnt[5] += C*j*1ull * (x - 1);
            }
            cnt[5] += A*i*1ull * c2(grt[i]);
        }
    }
    // 110
    {
        for (int k = 2; k < n; k++) {
            ull x = 0;
            for (int i:g[k])if(i<k) {
                x++;
                cnt[6] += A*1ull*i*1ull * (les[k] - x);
                cnt[6] += B*1ull*i*1ull * (x - 1);
            }
            cnt[6] += C*1ull*k*1ull * c2(les[k]);
        }
    }
    // 111
    {// find all triangle in O(MsqrtM)
        vector<int> id(n);
        iota(id.begin(), id.end(), 0);
        sort(id.begin(), id.end(), [&](auto& u, auto& v){
            return g[u].size() < g[v].size();
        });
        vector<int> ord(n);
        for (int i = 0; i < n; i++) {
            ord[id[i]] = i;
        }
        for (int i = 0; i < n; i++) {
            sort(g[i].begin(), g[i].end(), [&](auto& u, auto& v){
                return ord[u] > ord[v];
            });
        }
        vector<bool> trk(n);
        int x[3];
        for (int i: id) {
            for (int j: g[i])if(ord[j]<ord[i]){
                for (int k: g[j]) {
                    if(ord[k]<ord[j])break;
                    if (trk[k]) {
                        x[0]=i,x[1]=j,x[2]=k;
                        sort(x,x+3);
                        cnt[7] += A*x[0] + B*x[1] + C*x[2];
                    }
                }
                trk[j] = 1;
            }
            for (int j: g[i]) trk[j] = 0;
        }
    }
    ull res = 0;
    //if (n==200000) {
    //    // test #5
    //    // 14232614803193337856 1167695177061157504 8222692593356560064 85001344132000000 11546765848499709120 40119279086000000 84234194228000000 6292648000000
    //    for (int i = 0; i < 8; i++) {
    //        cout << cnt[i] << ' ';
    //    }
    //    return;
    //}
    //{ vector<ull> cnt = {14232614803193337856,
    //    1167695177061157504,
    //    8222692593356560064,
    //    85001344132000000,
    //    11546765848499709120,
    //    40119279086000000,
    //    84234194228000000,
    //    6292648000000};
    //    ull res = 0;
    //    for (int msk = 0; msk < 8; msk++) {
    //        //cerr<<cnt[msk]<<endl;
    //        if(__builtin_popcount(msk)&1) sub(res, cnt[msk]);
    //        else res += cnt[msk];
    //    }
    //    cout << res << endl;
    //}
    for (int msk = 0; msk < 8; msk++) {
        cerr<<cnt[msk]<<endl;
        if(__builtin_popcount(msk)&1) sub(res, cnt[msk]);
        else res += cnt[msk];
    }
    cout << res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
