#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int m = n/2;
    vector<int> cut;
    for (int i = 0; i < m; i++) {
        if (a[i] != a[i+1]) {
            cut.emplace_back(i+1);
        }
    }
    auto gg = [](){
        cout << "0 0 0\n";
    };
    if (cut.size() < 3) {
        gg(); return;
    }
    n = cut.size();
    // greedy pick leftmost g|s, pick rightmost b|none <=n/2
    // check exist valid s|b
    int g = cut[0];
    int gsb = cut[n-1];
    int s=-1,b=-1;
    for (int i = 1; i < n-1; i++) {
        if (cut[i]-g > g && gsb-cut[i] > g) {
            s = cut[i] - g;
            b = gsb-cut[i];
            break;
        }
    }
    if (s<=0) {
        gg(); return;
    }
    cout << g << ' '<< s << ' '<< b << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
