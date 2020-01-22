#include <bits/stdc++.h>

using namespace std;

// https://codeforces.com/blog/entry/73051?#comment-574496
vector<int> ask(string s) {
    cout << "? " << s << endl;
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;x--;
    }
    return a;
}
bool ck(string s, int i) {
    auto a = ask(s);
    return find(a.begin(), a.end(), i) != a.end();
}
void solve() {
    int n; cin >> n;
    string s(n, '?');
    char c[3] = {'C','H','O'};
    auto explore = [&](int k){
        assert(k+1<n && s[k]!='?' && s[k+1]!='?');
        int l = k, r = k+2;
        while (0<l || r<n) {
            if (0<l){
                for (int _ = 0; _ < 2; _++) {
                    if (ck(c[_] + s.substr(l,r-l), l-1)) {
                        s[--l] = c[_];
                        goto nxt;
                    }
                }
                s[--l] = c[2];
            } else {
                for (int _ = 0; _ < 2; _++) {
                    if (ck(s.substr(l,r-l) + c[_], l)) {
                        s[r++] = c[_];
                        goto nxt;
                    }
                }
                s[r++] = c[2];
            }
nxt:;
        }
        for (int i = 0; i < n; i++) {
            assert(s[i]!='?');
        }
    };
    for (string t: {"CH", "CO"}) {
        auto a = ask(t);
        if (!a.empty()) {
            int i = a[0];
            s[i] = t[0];
            s[i+1] = t[1];
            explore(i);
            cout << "! " <<  s << endl;
            return;
        }
    }

    auto oh = ask("OH");
    auto ho = ask("HO");
    // (O*|H*)C*
    if (oh.empty() && ho.empty()) {
        auto ccc = ask("CCC");
        if (ccc.empty()) {
            for (string t: {"OOC", "HHC"}) {
                auto a = ask(t);
                if (!a.empty()) {
                    assert(a.size()==1);
                    int k = a[0] + 2;
                    for (int i = 0; i < k; i++) {
                        s[i] = t[0];
                    }
                    for (int i = k; i < n; i++) {
                        s[i] = 'C';
                    }
                    cout << "! " << s << endl;
                    return;
                }
            }
            s.assign(n,'H');
            if(!ck(s, 0))s.assign(n,'O');
        } else {
            int k = ccc[0];
            for (int i = k; i < n; i++) {
                s[i] = 'C';
            }
            if (k>0){
                char p = ck("HCCC", k-1) ? 'H' : 'O';
                for (int i = 0; i < k; i++) {
                    s[i] = p;
                }
            }
        }
    // [OH,HO] C*
    } else {
        for (int i: oh) {
            s[i] = 'O'; s[i+1] = 'H';
        }
        for (int i: ho) {
            s[i] = 'H'; s[i+1] = 'O';
        }
        for (int i = n-2; i >= 0; i--) {
            if (s[i]=='?' && s[i+1]!='?') s[i] = s[i+1];
        }
        int k = 0;
        for (; k < n; k++) if (s[k]=='?')break;
        for (int i = k; i < n; i++) {
            if (ck(s.substr(0, i) + string(n-i, 'C'),  0)) {
                for (auto& x: s) {
                    if(x=='?')x='C';
                }
                break;
            }
            s[i] = s[i-1];
        }
    }
    cout << "! " << s << endl;
}

// keep in mind what format needed!! might WA!
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        solve();
        int verdict; cin >> verdict;
        assert(verdict == 1);
    }
    return 0;
}
