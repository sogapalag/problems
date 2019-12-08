#include <bits/stdc++.h>

using namespace std;

const int N = 101*2; 
int a[N][N];

// maintain two set |s|,|t| >= 2. |s|+|t|=n+1.
// keep remove lose of {s,t}. thus in the end, remain n best. and |s|,|t| not empty. and we don't compare between.
void solve() {
    int n; cin >> n;
    memset(a, 0, sizeof a);
    auto lose = [&](int i, int j){
        if (a[i][j]) return a[i][j];
        cout << "? " << i << ' ' << j << endl;
        string s; cin >> s;
        return a[i][j] = a[j][i] = s[0]=='<'?i:j;
    };
    set<int> s, t, rem;
    for (int i = 1; i <= 2; i++) {
        s.insert(i);
    }
    for (int i = 3; i <= n+1; i++) {
        t.insert(i);
    }
    for (int i = n+2; i <= 2*n; i++) {
        rem.insert(i);
    }
    auto get_lose = [&](set<int>& group){
        int res = *group.begin();
        for (int x: group) {
            if (x!=res) {
                res = lose(x,res);
            }
        }
        return res;
    };
    int cnt = 0;
    while (cnt < n) {
        int nxt = -1;
        if (!rem.empty()) {
            nxt = *rem.begin();
            rem.erase(nxt);
        }
        int l0 = get_lose(s);
        int l1 = get_lose(t);
        if (lose(l0, l1) == l0) {
            s.erase(l0);
            s.insert(nxt);
        } else {
            t.erase(l1);
            t.insert(nxt);
        }
        cnt++;
    }
    cout << '!' << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
