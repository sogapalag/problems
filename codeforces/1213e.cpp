#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    string s,t;
    cin >> s >> t;
    auto ck = [&](string e){
        return e.find(s) == string::npos && e.find(t) == string::npos;
    };
    auto rep = [](int n, string s){
        for (int _ = 0; _ < n; _++) {
            cout << s;
        }
    };
    cout << "YES\n";
    // no ->
    if (ck("abca")) {
        rep(n, "abc"); return;
    }
    // no <-
    if (ck("cbac")) {
        rep(n, "cba"); return;
    }
    // no ca
    if (ck("aabbcc")) {
        rep(n,"a"); rep(n,"b"); rep(n, "c"); return;
    }
    if (ck("bbccaa")) {
        rep(n, "b"); rep(n, "c"); rep(n, "a"); return;
    }
    if (ck("ccaabb")) {
        rep(n, "c"); rep(n, "a"); rep(n, "b"); return;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
