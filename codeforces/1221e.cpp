#include <bits/stdc++.h>

using namespace std;


// one: only B can use, so B can always take it in final step
// split: if B move, B can make it to one
// both: A/B only take one shot, when only 'both' remain, parity matters
void solve() {
    int a, b;
    cin >> a >> b;
    string s; cin >> s;
    s += "X";
    int split_len=-1;
    int one = 0, split = 0, both = 0;
    // [b,a)    [2b,..)     [a, 2b)
    int len = 0;
    for (char c: s){
        if (c == '.') len++;
        else {
            if (b <= len && len < a) one++;
            if (2*b <= len) split++, split_len=len;
            if (a <= len && len < 2*b) both++;
            len = 0;
        }
    }

    if (one > 0) {
        cout << "NO\n"; return;
    }
    if (split >= 2) {
        cout << "NO\n"; return;
    }
    if (split == 0) {
        cout << (both%2==0?"NO\n":"YES\n"); return;
    }
    assert(split==1 && split_len!=-1);
    bool anywin = false;
    for (int i = 0; i <= split_len - a; i++) {
        int k = split_len - a - i;
        if (b <= i && i < a) continue;
        if (b <= k && k < a) continue;
        if (2*b <= i) continue;
        if (2*b <= k) continue;
        int cnt = both;
        if (a <= i && i < 2*b) cnt++;
        if (a <= k && k < 2*b) cnt++;
        if (cnt%2==0) {
            anywin = true; break;
        }
    }
    cout << (anywin?"YES\n":"NO\n");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
