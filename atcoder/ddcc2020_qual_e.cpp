#include <bits/stdc++.h>

using namespace std;

const int N = 125;

int a[N*2];

void solve() {
    int n; cin >> n;
    auto q = [&](int x){
        cout << "? ";
        for (int i = 0; i < n; i++) {
            cout << x+i << ' ';
        }
        cout << endl;
        string s; cin >> s;
        return s[0] == 'R';
    };
    // bs flip l->r, thus (l, l+n) has equal RB
    a[1] = q(1); a[n+1] = a[1]^1;
    int l = 1, r = n+1;
    while (r-l > 1) {
        int m = (r+l)/2;
        a[m] = q(m);
        if (a[m] == a[l]) {
            l = m;
        } else {
            r = m;
        }
    }
    assert(r-l == 1);
    assert(a[l] != a[r]);
    a[l+n] = a[r];

    // use (l..l+n) query oth
    auto qoth = [&](int x){
        cout << "? ";
        cout << x << ' ';
        for (int i = l+1; i < l+n; i++) {
            cout << i << ' ';
        }
        cout << endl;
        string s; cin >> s;
        return s[0] == 'R';
    };
    for (int i = 1; i <= 2*n; i++) {
        if (i < l || i > l+n) {
            a[i] = qoth(i);
        }
    }

    // from oth get equal RB
    int m = (n-1)/2;
    int cnt[2] = {m,m};
    vector<int> pos;
    for (int i = 1; i <= 2*n; i++) {
        if (i <= l || i >= l+n) {
            if (cnt[a[i]] > 0) {
                pos.push_back(i);
                cnt[a[i]]--;
            }
        }
    }

    // use pos q (l..l+n)
    auto qin = [&](int x){
        cout << "? ";
        cout << x << ' ';
        for (int i: pos) {
            cout << i << ' ';
        }
        cout << endl;
        string s; cin >> s;
        return s[0] == 'R';
    };
    for (int i = 1; i <= 2*n; i++) {
        if (l < i && i < l+n) {
            a[i] = qin(i);
        }
    }
    string res;
    for (int i = 1; i <= 2*n; i++) {
        char x = a[i]?'R':'B';
        res += x;
    }
    cout << "! ";
    cout << res << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
