#include <bits/stdc++.h>

using namespace std;
using pi=pair<int, int> ;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int B = 20; // bucket 
const int G = 14; // giveup
const int N = 60; // each N/G

vector<int> cnt;
int win = 0;
//#define SIMULATE
int look(int v) {
#ifdef SIMULATE
    cnt[rng()%B + 1]++;
    return cnt[v];
#else
    int day; cin >> day;
    cout << v << " 0" << endl;
    int x; cin >> x;
    for (int _ = 0; _ < x; _++) {
        int _val;cin >> _val;
    }
    return x;
#endif
}
void add(int v, int i){
#ifdef SIMULATE
    if(i<100)cnt[rng()%B + 1]++; // last round is self
    cnt[v]++;
#else
    int day; cin >> day;
    cout << v << ' ' << i << endl;
#endif
}
// ave=100/20=5.
// so we waste evenly on G, N/G.. thus they will no chance with high prob.
// then use B days keep a history. 
//   keep dump for non-best greedily add minimum
// in the end add 100 to best
void solve() {
#ifdef SIMULATE
    cnt.assign(B+1, 0);
#else
#endif
    // add wasted
    for (int _ = 0, v = 1; _ < N; _++) {
        add(v, 1);
        v++; if(v>G)v=1;
    }
    vector<bool> del(B+1);
    for (int i = 1; i <= G; i++) {
        del[i] = true;
    }
    // hold a history
    vector<int> id(B);
    iota(id.begin(), id.end(), 1);
    shuffle(id.begin(), id.end(), rng);
    int best = -1, sz = 100;
    vector<int> hist(B+1);
    for (int i: id) {
        hist[i] = look(i);
        if (!del[i] && hist[i] < sz) {
            sz = hist[i];
            best = i;
        }
    }
    assert(best != -1);
    // keep waste threat
    priority_queue<pi,vector<pi>, greater<pi>> threat;
    for (int i: id) {
        if (i!=best) threat.push({hist[i], i});
    }
    for (int _ = 0; _ < 100-B-N-1; _++) {
        int sz,v;
        tie(sz,v) = threat.top(); threat.pop();
        add(v,1); threat.emplace(sz+1, v);
    }
    add(best, 100);
#ifdef SIMULATE
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return cnt[u] < cnt[v];
    });
    if (id[0] == best && cnt[best] < cnt[id[1]]) {
        win++;
    }
#else
#endif
}

// keep in mind what format needed!! might WA!
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        solve();
        //int verdict; cin >> verdict;
        //assert(verdict == 1);
    }
#ifdef SIMULATE
    cout << win << '\n';
    cout << double(win)/T;
#else
#endif
    return 0;
}
