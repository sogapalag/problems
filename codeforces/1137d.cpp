#include <bits/stdc++.h>

using namespace std;


void solve() {
    auto chase = [](){
        cout << "next 0 1" << endl;
        int _g; cin >> _g;
        for (int _ = 0; _ < _g; _++) {
            string __; cin >> __;
        }
        cout << "next 1" << endl;
        int g; cin >> g;
        for (int _ = 0; _ < g; _++) {
            string __; cin >> __;
        }
        return g == 2;
    };
    auto meet = [](){
        cout << "next 0 1 2 3 4 5 6 7 8 9" << endl;
        int g; cin >> g;
        for (int _ = 0; _ < g; _++) {
            string __; cin >> __;
        }
        return g == 1;
    };
    while (!chase()) {
        //
    }
    while (!meet()) {
        //
    }
    cout << "done" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
