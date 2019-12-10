#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// (--->i)(----->j) after ops i,j
// (<-----j)(--->i), we care ->i
void solve() {
    string S, t; 
    cin >> S >> t;
    int n = S.size();
    int a[2][2] = {};
    int b[2][2] = {};
    for (int i = 0; i < n; i+=2) {
        a[S[i]-'0'][S[i+1]-'0']++;
        b[t[i]-'0'][t[i+1]-'0']++;
    }
    if (a[0][0] != b[0][0] || a[1][1] != b[1][1]) {
        cout << "-1\n\n"; return;
    }

    vector<int> res;
    do {
        string s = S;
        res.clear();
        auto rev = [&](int p){
            if (!p) return;
            res.push_back(p);
            reverse(s.begin(), s.begin()+p);
        };
        for (int j = n-2; j >= 0; j-=2) {
            auto target = t.substr(j, 2);
            if (s.substr(j, 2) == target) continue;
            int i = 0;
            // move i back to j
            for (; i < j; i+=2) {
                if (s.substr(i, 2) == target) {
                    rev(i+2); rev(j+2); break;
                }
            }
            if (i >= j) {
                i = 0;
                swap(target[0], target[1]);
                // if not found, random flip a prefix contain i,
                // then we must have a same pattern
                for (; i <= j; i+=2) {
                    if (s.substr(i, 2) == target) {
                        break;
                    }
                }
                assert(i <= j);
                int k = rng() % ((j-i)/2 + 1);
                i += k*2;
                // repeat
                rev(i+2);
                j += 2;
            }
        }
        assert(s == t);
        //cout << res.size() << endl;
    } while ((int)res.size() > n+1);

    cout << res.size() << "\n";
    for (auto& x: res) {
        cout << x << ' ';
    }cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
