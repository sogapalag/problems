#include <bits/stdc++.h>

using namespace std;

void solve() {
    auto q = [](string s){
        cout << s << endl;
        int x; cin >> x;
        if(x==0)exit(0);
        return x;
    };
    int a = 300 - q(string(300,'a'));
    int b = 300 - q(string(300,'b'));

    string s; int d;
    if (a>b) {
        s = string(a+b, 'a');
        d = b;
    } else {
        s = string(a+b, 'b');
        d = a;
    }
    if (d==0) {
        cout << s; exit(0);
    }

    int n = a+b;
    auto flip = [](char& x){
        x = (x=='a'?'b':'a');
    };
    for (int i = 0; i < n-1; i++) {
        flip(s[i]);
        int x = q(s);
        if (x>d) flip(s[i]);
        else d = x;
    }
    if (d>0)flip(s[n-1]);
    cout << s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
