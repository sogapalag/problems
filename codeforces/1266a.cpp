#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s; cin >> s;
    bool zero = false;
    int sum = 0;
    int cnt = 0;
    for (char x: s) {
        zero |= x=='0';
        sum += (x-'0');
        if ((x-'0')%2==0)cnt++;
    }

    if (zero && cnt>=2 && sum%3==0) {
        cout << "red\n";
    }else{
        cout << "cyan\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
