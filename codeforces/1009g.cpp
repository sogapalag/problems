#include <bits/stdc++.h>

using namespace std;
const int L = 6;
const int N = 1<<L; 
int cnt_char[L];
int cnt_token[N];

bool hall() {
    // check S_msk = {sub}
    for (int msk = 0; msk < N; msk++) {
        int nei = 0;
        for (int i = 0; i < L; i++) {
            if (msk & (1<<i)) nei += cnt_char[i];
        }
        for (int sub = msk; sub > 0; (sub-=1)&=msk) {
            nei -= cnt_token[sub];
        }
        if (nei < 0) return false;
    }
    return true;
}

// O(n L 3^L)
void solve() {
    string s; cin >> s;
    for (char c: s) cnt_char[c-'a']++;
    vector<int> token(s.size(), N-1);
    int n; cin >> n;
    for (int _ = 0; _ < n; _++) {
        int p; cin >> p; p--;
        string t; cin >> t;
        int msk = 0;
        for (char c: t) msk |= 1<<(c-'a');
        token[p] = msk;
    }
    for (int t: token) cnt_token[t]++;

    if (!hall()) {
        cout << "Impossible"; return;
    }

    n = s.size();
    for (int i = 0; i < n; i++) {
        int msk = token[i];
        for (int c = 0; c < L; c++) {
            if (msk & (1<<c)) {
                if (cnt_char[c] == 0) continue;
                cnt_char[c]--;
                cnt_token[msk]--;
                if (hall()) {
                    s[i] = 'a'+c;
                    break;
                } else {
                    cnt_char[c]++;
                    cnt_token[msk]++;
                }
            }
        }
    }
    cout << s;
}

int sum_char[N];
int sum_token[N];

bool fast_hall() {
    for (int i = 0; i < N; i++) {
        if (sum_char[i] < sum_token[i]) return false;
    }
    return true;
}

// use SoS, O(n L 2^L)
void fast_solve() {
    string s; cin >> s;
    for (char c: s) cnt_char[c-'a']++;
    vector<int> token(s.size(), N-1);
    int n; cin >> n;
    for (int _ = 0; _ < n; _++) {
        int p; cin >> p; p--;
        string t; cin >> t;
        int msk = 0;
        for (char c: t) msk |= 1<<(c-'a');
        token[p] = msk;
    }
    for (int t: token) cnt_token[t]++;

    for (int i = 0; i < L; i++) {
        sum_char[1<<i] = cnt_char[i];
    }
    for (int i = 0; i < L; i++) {
        for (int msk = 0; msk < N; msk++) {
            if (msk & (1<<i)) {
                sum_char[msk] += sum_char[msk^(1<<i)];
            }
        }
    }
    memcpy(sum_token, cnt_token, sizeof sum_token);
    for (int i = 0; i < L; i++) {
        for (int msk = 0; msk < N; msk++) {
            if (msk & (1<<i)) {
                sum_token[msk] += sum_token[msk^(1<<i)];
            }
        }
    }
    if (!fast_hall()) {
        cout << "Impossible"; return;
    }

    n = s.size();
    for (int i = 0; i < n; i++) {
        int msk = token[i];
        for (int x = 0; x < N; x++) {
            if ((x&msk) == msk) sum_token[x]--;
        }
        for (int c = 0; c < L; c++) {
            if (msk & (1<<c)) {
                if (cnt_char[c] == 0) continue;
                cnt_char[c]--;
                for (int x = 0; x < N; x++) {
                    if (x & (1<<c)) sum_char[x]--;
                }
                if (fast_hall()) {
                    s[i] = 'a'+c;
                    break;
                } else {
                    cnt_char[c]++;
                    for (int x = 0; x < N; x++) {
                        if (x & (1<<c)) sum_char[x]++;
                    }
                }
            }
        }
    }
    cout << s;
}

// there is a way direct dynamic-modify flow on dinic. hard to maintain. omit
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fast_solve();
    cout << endl;
}
