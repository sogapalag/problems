#include <bits/stdc++.h>

using namespace std;


void solve() {
    int res[4];
    cout << "? 1 2" << endl;
    fflush(stdout);
    cin >> res[0];
    cout << "? 2 3" << endl;
    fflush(stdout);
    cin >> res[1];
    cout << "? 4 5" << endl;
    fflush(stdout);
    cin >> res[2];
    cout << "? 5 6" << endl;
    fflush(stdout);
    cin >> res[3];
    vector<int> a = {4, 8, 15, 16, 23, 42};
    do{
        if (a[0]*a[1] == res[0] && a[1]*a[2] == res[1] && a[3]*a[4] == res[2] && a[4]*a[5] == res[3]){
            cout << "! ";
            for (auto& x: a) {
                cout << x << ' ';
            }
        fflush(stdout);
            return;
        }
    } while(next_permutation(a.begin(), a.end()));
}

int main() {
    solve();
    cout << endl;
}
