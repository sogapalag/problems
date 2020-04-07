#include <bits/stdc++.h>
#include "rail.h"

using namespace std;

//int getDistance(int i, int j);

// first it's easy to note shortest be right-nearest ')'
// key focus if we process by d_0 order
//    ()..)  ((( )  ((..()  (..()
//     ord   0        ord    ord
// note the form of ord-block relative ord when process
// L: till now, left-most '('
// R: ')'
// for each u there're 4 cases
// L(R
// L)R
// LR)
// (LR
// note )LR, LR( won't occur cause relative ord
// with x,y,D. exactly one x/y is turnning, let it be z.
// one can see z = a[L]+D - (x+y-D)/2 same in 4 cases.
// 4 cases separate by x,y </> D,  mp[z] = (/)
// so there won't be >1 cases holds.
//
// another note, there might be mp[z] = 0, i.e. the turning could process later
// one can see this case must >D cases.
// and (/) can differ by whether a[0]+d_0[u] = a[L]+x.
//   since if turnning from L->u, can use R_0(contradict to mp=0) or some near ) thus dist should be less
void findLocation(int n, int x0, int a[], int t[]) {
    vector<int> mp((int)1e6+10);
    mp[a[0] = x0] = t[0] = 1;
    if (n == 1) return;
    vector<int> d(n);
    for (int i = 1; i < n; i++) {
        d[i] = getDistance(0, i);
    }
    int L = 0;
    int R = min_element(d.begin()+1, d.end()) - d.begin();
    mp[a[R] = a[L]+d[R]] = t[R] = 2;
    vector<pair<int,int>> candi;
    for (int i = 0; i < n; i++) {
        if (i!=L&&i!=R) candi.emplace_back(d[i], i);
    }
    sort(candi.begin(), candi.end());
    //vector<int> id(n);
    //iota(id.begin(), id.end(), 0);
    //sort(id.begin(), id.end(), [&](auto& u, auto& v){
    //    return d[u] < d[v];
    //});
    //for (int _ = 2; _ < n; _++) {
    //    int u = id[_];
    for (int _ = 0; _ < n-2; _++) {
        int u = candi[_].second;
        int D = a[R] - a[L];
        int x = getDistance(L, u);
        int y = getDistance(R, u);
        // x,y > D, z might (time)later process mp[z]=0
        if (x < D) {
            int z = a[L] + x - (x+y - D)/2;
            if (a[L]<=z && z<=a[R] && mp[z] == 1) {
                mp[a[u] = a[L]+x] = t[u] = 2; continue;
            }
        } else {
            int z = a[L] + x - (x+y - D)/2;
            if (a[L]<=z && z<=a[R] && mp[z] == 1) {
                mp[a[u] = a[L]+x] = t[R = u] = 2; continue;
            }
        }

        if (y < D) {
            int z = a[R] - y + (x+y - D)/2; // z'=z, check [a[L],a[R]] can omit
            if (a[L]<=z && z<=a[R] && mp[z] == 2) {
                mp[a[u] = a[R]-y] = t[u] = 1; continue;
            }
        } else {
            int z = a[R] - y + (x+y - D)/2;
            if (a[L]<=z && z<=a[R] && mp[z] == 2) {
                mp[a[u] = a[R]-y] = t[L = u] = 1; continue;
            }
        }

        if (a[L]+x == a[0]+d[u]) {
            mp[a[u] = a[L]+x] = t[R = u] = 2;
        } else {
            mp[a[u] = a[R]-y] = t[L = u] = 1;
        }
    }
}
