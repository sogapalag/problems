#include <bits/stdc++.h>

using namespace std;

struct Node {
    int x, y;
    Node() {}
    Node(int _x, int _y) : x(_x), y(_y) {}
};

vector<int> g[2][2];
vector<int> res;

// another way, divide, x+y=0/1. if not work, rotate 45
void solve() {
    int n; cin >> n;
    vector<Node> a(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        a[i] = {x,y};
    }
#define rep(i) for(int i=0;i<2;i++)
    // by pairty
    while (true) {
        rep(i)rep(j)g[i][j].clear();

        for (int i = 0; i < n; i++) {
            g[a[i].x&1][a[i].y&1].push_back(i);
        }
        int cnt = g[0][0].size() + g[1][1].size();
        // 00 11 | 01 10.  0/1 mod 2
        if (cnt>0 && cnt<n) {
            for (int x: g[0][0]) res.push_back(x);
            for (int x: g[1][1]) res.push_back(x);
            break;
        } else {
            // 00 | 11.   2/4 mod 4
            if (cnt==n) {
                cnt = g[0][0].size();
                if (cnt>0 && cnt < n) {
                    for (int x: g[0][0]) res.push_back(x);
                    break;
                }
            // 01 | 10.  2/4 mod 4
            } else {
                cnt = g[0][1].size();
                if (cnt>0 && cnt < n) {
                    for (int x: g[0][1]) res.push_back(x);
                    break;
                }
            }
        }
        // half scale
        for (auto& o: a) {
            if (o.x&1)o.x+=1;
            if (o.y&1)o.y+=1;
            o.x/=2; o.y/=2;
        }
    }

    cout << res.size() << "\n";
    for (int x: res) {
        cout << x+1 << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
