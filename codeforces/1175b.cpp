#include <bits/stdc++.h>

using namespace std;


// never use char again..
void solve() {
    int n; cin >> n;
    long long x = 0;
    long long bound = (1ll << 32) - 1;
    vector<long long> stk;
    vector<long long> a(n, 0);
    auto gg = [&](){
        cout << "OVERFLOW!!!" << endl;
        exit(0);
    };
    for (int i = 0; i < n; i++) {
        //char op[3];
        string op;
        cin >> op;
        if (op[0] == 'a') {
            a[stk.size()]++;
            if (a[stk.size()] > bound) gg();
        }
        if (op[0] == 'f') {
            long long k; cin >> k;
            stk.emplace_back(k);
            a[stk.size()] = 0ll;
        }
        if (op[0] == 'e') {
            long long tmp = a[stk.size()] * stk.back();
            if (tmp > bound) gg();
            stk.pop_back();
            a[stk.size()] += tmp;
            if (a[stk.size()] > bound) gg();
        }
    }
    x = a[0];
    if (x > bound) gg();
    cout << x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
