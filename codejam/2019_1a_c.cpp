#include <bits/stdc++.h>

using namespace std;

const int N = 1024; 
const int W = 52; 
const int A = 26; 
int trie[N*W][A], cnt;
int pre[N*W], freq[N*W];
void insert(string& s) {
    int x = 0;
    for (char c: s) {
        int d = c - 'A';
        int& nxt = trie[x][d];
        if (nxt == 0) {
            pre[cnt] = x;
            nxt = cnt++;
        }
        x = nxt;
        freq[x]++;
    }
}


void solve() {
    int n; cin >> n;
    memset(trie, 0, sizeof trie);
    cnt = 1;
    memset(pre, 0, sizeof pre);
    memset(freq, 0, sizeof freq);
    for (int _ = 0; _ < n; _++) {
        string s; cin >> s;
        reverse(s.begin(), s.end());
        insert(s);
    }
    int res = 0;
    // backwards greedy pair longer
    for (int i = cnt-1; i >= 1; i--) {
        if (freq[i] < 2) continue;
        res++;
        int x = i;
        while (x) {
            freq[x] -= 2;
            x = pre[x];
        }
    }
    cout << 2*res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
