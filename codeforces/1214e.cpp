#include <bits/stdc++.h>

using namespace std;

struct Node {
    int i,k;
    Node() {}
    Node(int _i, int _k):i(_i),k(_k){}
    bool operator<(const Node& _n)const{
        return k>_n.k;
    }
};

void solve() {
    int n; cin >> n;
    vector<Node> a(n<<1);
    for (int i = 0; i < n; i++) {
        int x;cin >> x;
        a[i] = {2*i+1, x};
    }
    sort(a.begin(), a.begin()+n);
    auto lk = [](int u,int v){
        cout << u << ' ' << v << "\n";
    };
    for (int i = 1; i < n; i++) {
        lk(a[i-1].i, a[i].i);
    }
    int r = n;
    for (int i = 0; i < n; i++) {
        int x = i+a[i].k;
        int u = a[i].i+1;
        assert(x <= r);
        if (x < r) {
            lk(a[x-1].i, u);
        } else {
            a[r].i = u;
            lk(a[r-1].i, u);
            r++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
