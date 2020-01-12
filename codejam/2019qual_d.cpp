#include <bits/stdc++.h>

using namespace std;

int n,b,f;
// each col indicate its index
void easy() {
    vector<string> s(f, string(n,'#'));
    for (int x = 0; x < n; x++) {
        for (int i = 0; i < f; i++) {
            s[i][x] = '0' + (x>>i&1);
        }
    }
    vector<string> got;
    for (auto& x: s) {
        cout << x << '\n' << flush;// fflush(stdout);
        string t; cin >> t;
        got.push_back(t);
    }
    vector<bool> trk(n);
    for (int _ = 0; _ < n-b; _++) {
        int x = 0;
        for (int i = 0; i < f; i++) {
            int bit = got[i][_] - '0';
            x |= bit<<i;
        }
        trk[x] = true;
    }
    for (int i = 0; i < n; i++) {
        if (!trk[i]) cout << i << ' ';
    }
    cout << '\n' << flush; //fflush(stdout);
}
void hard() {
    vector<string> s(f, string(n,'#'));
    const int BLOCK = 32; 
    for (int x = 0, y = 0; x < n; x++, (y+=1)%=BLOCK) {
        for (int i = 0; i < f; i++) {
            s[i][x] = '0' + (y>>i&1);
        }
    }
    vector<string> got;
    for (auto& x: s) {
        // this way flush.. otherwise TLE.
        cout << x << '\n' << flush; //fflush(stdout);// << endl;
        string t; cin >> t;
        got.push_back(t);
    }
    vector<int> a;
    for (int _ = 0; _ < n-b; _++) {
        int x = 0;
        for (int i = 0; i < f; i++) {
            int bit = got[i][_] - '0';
            x |= bit<<i;
        }
        a.push_back(x);
    }
    //int z = 0;
    //for (int x: a) {
    //    while ((z&31) != x) {
    //        cout << z++ << ' ';
    //    }
    //    z++;
    //}
    //while (z < n) {
    //    cout << z++ << ' ';
    //}
    //cout << '\n' << flush;
     
    vector<bool> trk(n);
    trk[a[0]] = true;
    for (int i = 1, ib = 0; i < n-b; i++) {
        if (a[i-1] > a[i]) ib++;
        //a[i] += ib * BLOCK;  // modify will influ follow compare
        trk[a[i] + ib*BLOCK] = true;
    }
    for (int i = 0; i < n; i++) {
        if (!trk[i]) cout << i << ' ';
    }
    cout << '\n' << flush; //fflush(stdout);//cout << endl;
}
void solve() {
    cin >> n >> b >> f;
    if (f==10) easy();
    else hard();
    int x; cin >> x; // will get 1/-1
    if (x==-1) exit(-1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        //cout << "Case #" << t << ": ";
        solve();
        //cout << "\n";
    }
    fflush(stdout);
}
