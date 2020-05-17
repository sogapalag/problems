#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}
void solve() {
    int n,k;
    cin >> n >> k;
    auto qry = [&](auto a, auto b){
        cout << "? " << a.size() << ' ' << b.size() << endl;
        for (auto& x: a) {
            cout << x << ' ';
        }cout << endl;
        for (auto& x: b) {
            cout << x << ' ';
        }
        cout << endl;
        string s; cin >> s;
        if (s[0]=='F') return '>';
        if (s[0]=='S') return '<';
        return '=';
    };
    auto f = [&](){
        int x = rng()%(n-1) + 2;
        cout << "? 1 1" << endl;
        cout << "1" << endl;
        cout << x << endl;
        string s; cin >> s;
        if (s[0]=='F') return '>';
        if (s[0]=='S') return '<';
        return '=';
    };
    // 1 is heavey?
    for (int _ = 0; _ < 25; _++) {
        if (f() == '<') {
            cout << "! 1" << endl; return;
        }
    }
    queue<int> q;
    for (int i = 2; i <= n; i++) {
        q.push(i);
    }
    vector<int> a{1};
    // double heavey size, until find smaller, then bs it.
    while (true) {
        vector<int> b;
        while (!q.empty() && b.size() < a.size()) {
            b.push_back(q.front()); q.pop();
        }
        while (b.size() < a.size()) {
            a.pop_back();
        }
        auto r = qry(a,b);
        assert(r != '<');
        if (r == '=') {
            for (auto& x: b) {
                a.push_back(x);
            }
        } else {
            if (b.size()==1) {
                cout << "! " << b[0] << endl;
            } else {
                int i = bs_first<int>(1, b.size()+1, [&](int i){
                        return qry(vector<int>(a.begin(), a.begin()+i), vector<int>(b.begin(), b.begin()+i)) == '>';
                        });
                cout << "! " << b[i-1] << endl;
            }
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
