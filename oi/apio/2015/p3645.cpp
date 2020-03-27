#include <bits/stdc++.h>

using namespace std;

using ll=long long;
const int N = 3e4+10; 
ll d[N*300];
int to[N*300];
int down[N*300];
vector<int> small[N];
vector<int> large[N];

// n<= u < K, for each step j
// -  id(i,j)->id(i+-j, j) with 1, id(i,j) can goto i with 0.    for j < B
// -  u<n can goto small[u] with 0. (i.e. same build switch)
// -  create help-vertex, for j>=B
//                            i+j        i+2j
//                             ^          ^
//                             |0         |0         .
//                     i ->1 (i+j)' ->1 (i+2j)' ->1 ...
//                             
void solve() {
    int n,m;
    cin >> n >> m;
    const int B = min((int)sqrt(n), 100); 
    const int K = n * B; 
    auto id = [&](int i, int d){
        return d*n + i;
    };
    int s, t;
    int tot = K;
    for (int _ = 0; _ < m; _++) {
        int i,j;
        cin >> i >> j;
        if (_==0)s=i;
        if (_==1)t=i;
        if (j < B) {
            small[i].push_back(id(i,j));
        } else {
            for (int r = i+j, crt = i; r < n; r+=j) {
                int nxt = tot++;
                if (crt < n) large[crt].push_back(nxt);
                else to[crt] = nxt;
                down[nxt] = r;
                crt = nxt;
            }
            for (int l = i-j, crt = i; l >= 0; l-=j) {
                int nxt = tot++;
                if (crt < n) large[crt].push_back(nxt);
                else to[crt] = nxt;
                down[nxt] = l;
                crt = nxt;
            }
        }
    }
    if (s==t) {
        cout << 0; return;
    }
    // 01bfs
    memset(d, 0x3f, sizeof d);
    d[s] = 0;
    deque<int> q;
    q.push_front(s);
#define ck0 if(d[v]>d[u]) {\
    d[v]=d[u];\
    q.push_front(v);\
    }
#define ck1 if(d[v]>d[u]+1) {\
    d[v]=d[u]+1;\
    q.push_back(v);\
    }
    while (!q.empty()) {
        int u = q.front();
        if (u == t) {
            cout << d[t]; exit(0);
        }
        q.pop_front();
        if (u < n) {
            for (int v: small[u]) ck0;
            for (int v: large[u]) ck1;
        } else if (u < K) {
            int v = u%n, j = u/n;
            ck0;
            for (int k:{v-j,v+j}) {
                if (0<=k && k<n) {
                    int v = id(k,j);
                    ck1;
                }
            }
        } else {
            int v = down[u]; ck0;
            v = to[u];
            if (v) ck1;
        }
    }
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
