#include <bits/stdc++.h>

using namespace std;
#define LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(bool x) { return (x ? "T" : "F"); }
string to_string(const char* s) { return to_string((string)s); }
template <typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename V>
string to_string(V v) {
    bool f = true; string res = "[";
    for (const auto& x: v) {
        if (!f) res += ", ";
        f = false;
        res += to_string(x); } res += "]";
    return res;
}
void debug() { cerr << endl; }
template <typename H, typename... T>
void debug(H h, T... t) { cerr << " " << to_string(h); debug(t...); }
#ifdef LOCAL
#define dbg(args...) cerr<<"("<<#args<<") =", debug(args)
#else
#define dbg(args...) 2019
#endif

using ll=long long ;

struct Node {
    int x,i;
    Node() {}
    Node(int _x,int _i):x(_x),i(_i){}
    bool operator<(const Node& _n)const{
        return x < _n.x;
    }
};

// there is a ternary method mid, mid+1. proof?
void solve() {
    int m,n;
    cin >> m >> n;
    vector<Node> a(n), b(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x; x--;
        a[i] = {x, i};
    }
    for (int i = 0; i < n; i++) {
        int x; cin >> x; x--;
        b[i] = {x, i};
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int ha = m/2, ce = (m+1)/2;
    vector<ll> s(n);
    int i,j;
    // offset
#define k (n+j-i)%n
    // easy causing bug, focus on first offset can use new repre.
    for (i = 0; i < n; i++) {
        int x = a[i].x;
        if (x < ha) {
            // notice s[..]=0,
            j = 0;
            s[k] += -m;
            j = lower_bound(b.begin(), b.end(), Node{x,-1}) - b.begin();
            s[k] += -2ll*x;
            j = lower_bound(b.begin(), b.end(), Node{x+ce,-1}) - b.begin();
            s[k] += 2ll*x + m;
        } else {
            j = 0;
            s[k] += m;
            j = lower_bound(b.begin(), b.end(), Node{x-ha,-1}) - b.begin();
            s[k] += 2ll*x-m;
            j = lower_bound(b.begin(), b.end(), Node{x, -1}) - b.begin();
            s[k] += -2ll*x;
        }
    }
    for (j = 0; j < n; j++) {
        int x = b[j].x;
        if (x < ce) {
            // since j-i, offset grows as i dec. focus on which offset use new repre.
            i = n-1;
            s[k] += 0;
            i = upper_bound(a.begin(), a.end(), Node{x+ha,-1}) - a.begin()-1;
            s[k] += -2ll*x;
            i = upper_bound(a.begin(), a.end(), Node{x,-1}) - a.begin()-1;
            s[k] += 2ll*x;
        } else {
            i = n-1;
            s[k] += 0;
            i = upper_bound(a.begin(), a.end(), Node{x,-1}) - a.begin()-1;
            s[k] += 2ll*x;
            i = upper_bound(a.begin(), a.end(), Node{x-ce,-1}) - a.begin()-1;
            s[k] += -2ll*x;
        }
    }
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        int x = (a[i].x - b[i].x + m) % m;
        int y = (b[i].x - a[i].x + m) % m;
        sum += min(x,y);
    }
    s[0] = sum;
    for (int t = 1; t < n; t++) {
        s[t] += s[t-1];
    }
    int t = min_element(s.begin(), s.end()) - s.begin();
    cout << s[t] << "\n";
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        res[a[i].i] = b[(i+t)%n].i + 1;
    }
    for (auto& x: res) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
