#include <bits/stdc++.h>

using namespace std;

using Freq=array<int,26>;
map<Freq, int> mp[111];
Freq operator+(const Freq& a, const Freq& b){
    Freq r = {};
    for (int i = 0; i < 26; i++) {
        r[i] = a[i] + b[i];
    }
    return r;
}
Freq operator-(const Freq& a, const Freq& b){
    Freq r = {};
    for (int i = 0; i < 26; i++) {
        r[i] = a[i] - b[i];
    }
    return r;
}
Freq cnt[111] = {};

Freq f(string s){
    Freq a = {};
    for (char x: s)a[x-'a']++;
    return a;
}
void solve() {
    int n; cin >> n;
    cout << "? 1 " << n << endl;
    string s;
    for (int _ = 0; _ < (n)*(n+1)/2; _++) {
        cin >> s;
        cnt[s.size()] = cnt[s.size()] + f(s);
        //mp[s.size()][f(s)]++;
    }
    if (n == 1) {
        cout << "! "<< s; return;
    }
    int m = n/2;
    cout << "? 1 " << m << endl;
    for (int _ = 0; _ < m*(m+1)/2; _++) {
        cin >> s;
        mp[s.size()][f(s)]++;
    }
    string res(n, '#');
    if (2 <= m) {
        cout << "? 2 " << m << endl;
        for (int _ = 0; _ < (m)*(m-1)/2; _++) {
            cin >> s;
            auto it = mp[s.size()].find(f(s));
            it->second--;
            if (it->second == 0) {
                mp[s.size()].erase(it);
            }
        }
        for (int i = 1; i <= m; i++) {
            auto c = mp[i].begin()->first;
            for (int k = 0; k < i-1; k++) {
                c[res[k]-'a']--;
            }
            for (int x = 0; x < 26; x++) {
                if (c[x]) {
                    res[i-1] = 'a'+x;
                    break;
                }
            }
        }
    } else {
        res[0] = s[0];
    }
    for (int i = m, pos = m; i >= 0; i--) {
        if (i*2==n) continue;
        // key part, diff is s[i...n-i)
        auto c = cnt[i+1] - cnt[i];
        for (int k = pos-1; k >= i; k--) {
            c[res[k]-'a']--;
        }
        for (int _ = 0; _ < 26; _++) {
            if (c[_] > 0) {
                res[pos++] = 'a'+_;
                break;
            }
        }
    }
    cout << "! " << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
