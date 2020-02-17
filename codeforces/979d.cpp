#include <bits/stdc++.h>

using namespace std;

const int L = 18; 
const int N = 100005; 
vector<int> divs[N];
struct Node {
    int ch[2];
    int mi;
    Node() {
        ch[0] = ch[1] = 0;
        mi = N;
    }
};
vector<Node> trie[N];
int ptr[N];
void prep() {
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j+=i) {
            divs[j].push_back(i);
        }
        trie[i].emplace_back();
        ptr[i] = 1;
    }
}
bool trk[N];
void insert(int d, int x) {
    auto& tr = trie[d];
    auto& p = ptr[d];
    tr[0].mi = min(tr[0].mi, x);
    int crt = 0;
    for (int i = L-1; i >= 0; i--) {
        //! ERROR!!!!, cannot use ref to struct member?????
        //! 
        //int& to = tr[crt].ch[x>>i&1];
        ////cerr<<"to" << to<<endl;
        //if (to == 0) {
        //    tr.emplace_back();
        //    to = p++;
        //}

        //! ERROR!!!!, pointer not allowed, neither.. for safety?
        //int* to = &tr[crt].ch[x>>i&1];
        //if (*to == 0) {
        //    tr.emplace_back();
        //    *to = p++;
        //}
        //crt = *to;

        if (tr[crt].ch[x>>i&1] == 0) {
            tr.emplace_back();
            tr[crt].ch[x>>i&1] = p++;
        }
        crt = tr[crt].ch[x>>i&1];

        tr[crt].mi = min(tr[crt].mi, x);
    }
    //cerr<<'?'<<tr[0].ch[0] << endl;
}
int query(int x, int d, int s) {
    if (x % d != 0) return -1;
    auto& tr = trie[d];
    if (tr[0].mi + x > s) return -1;
    int lim = s - x;
    int crt = 0;
    int res = 0;
    for (int i = L-1; i >= 0; i--) {
        int z = x>>i&1;
        if (tr[crt].ch[z^1] && tr[ tr[crt].ch[z^1] ].mi <= lim) {
            res |= (z^1)<<i;
            crt = tr[crt].ch[z^1];
        } else {
            res |= z<<i;
            crt = tr[crt].ch[z];
            assert(crt);
        }
        //cerr<< i <<' '<< z<< ' '<<crt<<endl;
    }
    return res;
}

void solve() {
    prep();
    int q; cin >> q;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int x; cin >> x;
            if (!trk[x]) {
                trk[x] = 1;
                for (int d: divs[x]) insert(d, x);
            }
        } else {
            int x,d,s;
            cin >> x >> d >> s;
            cout << query(x,d,s) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
