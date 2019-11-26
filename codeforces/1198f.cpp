#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    clock_t begin = clock();
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    vector<int> res(n);

    while (clock() - begin <= 450) {
        shuffle(p.begin(), p.end(), rng);
        int g[2] = {0, 0};
        int k = 0;
        for (int i = 0; i < n; i++) {
            g[k] = __gcd(g[k], a[p[i]]);
            res[p[i]] = k+1;
            if (k == 0 && g[0] == 1) k++;
        }
        if (g[0] == 1 && g[1] == 1) {
            cout << "YES\n";
            for (auto& x: res) {
                cout << x << ' ';
            }
            return;
        }
    }
    cout << "NO";
}
void solve2() {
    clock_t begin = clock();
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    vector<int> res(n);

    while (clock() - begin <= 450) {
        shuffle(p.begin(), p.end(), rng);
        int g[2] = {a[p[0]], 0};
        res[p[0]] = 1;
        for (int i = 1; i < n; i++) {
            if (a[p[i]] % g[0] == 0) {
                g[1] = __gcd(g[1], a[p[i]]);
                res[p[i]] = 2;
            } else {
                g[0] = __gcd(g[0], a[p[i]]);
                res[p[i]] = 1;
            }
        }
        if (g[0] == 1 && g[1] == 1) {
            cout << "YES\n";
            for (auto& x: res) {
                cout << x << ' ';
            }
            return;
        }
    }
    cout << "NO";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve2();
    cout << endl;
}
