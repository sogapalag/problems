#include <bits/stdc++.h>
#include "towns.h"
using namespace std;

//int getDistance(int u, int v);

// first one can easily get 5n solution
// 2n (diam) + n (body-pos) + 2n (BM),
// body-pos recall caterpillar-tree, we might need to check its sz. with at most one candidate center 
// BM recall Boyer–Moore majority vote algorithm.
// key optim to 3.5n
// (2n+n) -> 2n, if S==R easy, else note we only care body-pos info, one can figure out it's enough, without additional n queries
// (2n) -> 1.5n, note after n queries get dominated group. we only need at most 0.5n additional queries to join those deleted candidate. since #cnt_t==0 + #sz==0 >= n/2.
int hubDistance(int n, int sub) {
    int S = 0;
    vector<int> ds(n);
    for (int i = 0; i < n; i++) {
        if (i != S) ds[i] = getDistance(i, S);
    }
    int L = max_element(ds.begin(), ds.end()) - ds.begin();
    vector<int> dl(n);
    dl[S] = ds[L];
    for (int i = 0; i < n; i++) {
        if (i != L && i != S) {
            dl[i] = getDistance(i, L);
        }
    }
    int R = max_element(dl.begin(), dl.end()) - dl.begin();
    if (dl[R] == dl[S]) R = S;
    int diam = dl[R];
    int radius = diam;
    bool cen = false;
    vector<int> candi; int loc = -1;
    map<int,vector<int>> body;
    if (S == R) {
        auto& dr = ds;
        for (int i = 0; i < n; i++) {
            if (i != L && i != R) {
                int x = dl[i] + diam - dr[i];
                assert(x > 0 && x % 2 == 0);
                x /= 2;
                body[x].push_back(i);
                radius = min(radius, max(x, diam-x));
            }
        }
    } else {
        int M = dl[S] + diam - ds[R];
        M /= 2;
        body[M].push_back(S);
        radius = min(radius, max(M, diam-M));
        for (int i = 0; i < n; i++) {
            if (i != L && i != S) {
                //int x = dl[i] + diam - ds[i];
                int x = dl[i] + dl[S] - ds[i];
                x /= 2;
                x = min(x, M);
                radius = min(radius, max(x, diam - x));
                body[x].push_back(i);
            }
        }
    }
    {
        int left = 1;
        for (auto& _: body) {
            int x = _.first;
            auto& a = _.second;
            int sz = a.size();
            if (radius == max(x, diam-x)) {
                if (left <= n/2 && (n-left-sz) <= n/2) {
                    if (sz <= n/2) cen = true;
                    else candi = a, loc = x;
                }
            }
            left += sz;
        }
    }
    if (sub <= 2) return radius;
    if (cen) return radius;
    if (candi.empty()) return -radius;
    // 
    auto same = [&](int u, int v){
        int z = getDistance(u, v);
        return dl[u]+dl[v] - loc*2 > z;
    };
    // Boyer–Moore majority vote algorithm
    {
        int dom = -1, cnt = 0;
        vector<int> sz(n, 1);
        for (int u:candi) {
            if (!cnt) dom = u, cnt = 1;
            else if (same(u, dom)) {
                ++sz[dom]; --sz[u];
                ++cnt;
            } else --cnt;
        }
        for (int u:candi) {
            if (u != dom && sz[u] > 0) {
                if (same(u, dom)) sz[dom] += sz[u];
            }
        }
        return sz[dom] <= n/2 ? radius : -radius;
    }
}
