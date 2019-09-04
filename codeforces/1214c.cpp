#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    if (n&1) {
        cout << "No"; return;
    }
    string s; cin >> s;
    int cnt = 0;
    for (char x:s)
        if(x=='(')cnt++;
    if (cnt != n/2) {
        cout << "No"; return;
    }
    auto ck = [&](){
        int stk = 0;
        for (char x:s) {
            if (x =='(') stk++;
            else {
                if (stk==0) return false;
                stk--;
            }
        }
        return stk==0;
    };
    if (ck()) {
        cout << "Yes"; return;
    }
    int i=0;
    while (s[i]!=')') {
        i++;
    }
    s[i] = '#';
    s+=")";
    auto ck2 = [&](){
        int stk = 0;
        for (char x:s) {
            if (x =='(') stk++;
            else if (x==')'){
                if (stk==0) return false;
                stk--;
            }
        }
        return stk==0;
    };
    cout << (ck2()?"Yes":"No");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
