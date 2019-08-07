#include <bits/stdc++.h>

using namespace std;

using ll=long long;

struct Node {
    int x,y;
    Node() {}
};

ll dp[2][2]; // [crt/nxt][l/r] end with l/r y, min cost
int c[2][2]; // [crt/nxt][l/r] y
int dis[2][2]; // [from l/r][to l/r] additional min cost


// for each level, left-y, right-y matter
void solve() {
    int n,m,k,q;
    cin >> n >> m >> k >> q;
    vector<Node> a(k);
    for (auto& p: a) {
        cin >> p.x >> p.y;
    }
    vector<int> b(q);
    for (auto& y: b) {
        cin >> y;
    }
    sort(a.begin(), a.end(), [](auto& u, auto& v){
            return u.x < v.x || (u.x==v.x && u.y < v.y);
            });
    b.push_back(1<<29); //for easy corner condition
    b.push_back(-(1<<29));
    sort(b.begin(), b.end());
    const int UP = a[k-1].x - 1;

    int i = 0;
    while (i < k && a[i].x == 1) {
        i++;
    }
    memset(dp, 0, sizeof dp);
    c[0][0] = c[0][1] = 1;
    if (i > 0) {
        int y = a[i-1].y;
        c[0][0] = c[0][1] = y;
        dp[0][0] = dp[0][1] = y-1;
    }
    int crt = 0;
    while (i < k) {
        int nxt = crt^1;
        int I = i;
        while (i < k && a[i].x == a[I].x) {
            i++;
        }
        c[nxt][0] = a[I].y;
        c[nxt][1] = a[i-1].y;
        int width = c[nxt][1] - c[nxt][0];
        for (int from: {0,1}) {
            for (int to: {0,1}) {
                int s = c[crt][from], t = c[nxt][to^1];
                if (s < t) swap(s,t); //dual
                int j = lower_bound(b.begin(), b.end(), s) - b.begin();
                int v = lower_bound(b.begin(), b.end(), t) - b.begin();

                if (b[v] <= s) {
                    dis[from][to] = s-t + width;
                } else {
                    dis[from][to] = min(2*b[j]-s-t, s+t-2*b[v-1]) + width;
                }

            }
        }
        for (int to: {0,1}) {
            dp[nxt][to] = min(dp[crt][0]+dis[0][to], dp[crt][1]+dis[1][to]);
        }

        crt ^= 1;
    }

    ll res = min(dp[crt][0], dp[crt][1]) + UP;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
