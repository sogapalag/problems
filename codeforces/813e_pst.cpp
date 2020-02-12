#include <bits/stdc++.h>

using namespace std;

struct PstNode {
    using Ptr = PstNode*;
    Ptr ch[2] = {nullptr, nullptr};
    int x = 0;
    PstNode() {}
    PstNode(int _x) : x(_x){}

    void pull() {
        x = ch[0] ? ch[0]->x : 0;
        x +=ch[1] ? ch[1]->x : 0;
    }
    Ptr add(int p, int dx, int sl, int sr) {
        if (sr - sl == 1) {
            return new PstNode(x + dx);
        }
        int sm = sl + (sr-sl)/2;
        auto nd = new PstNode();
        nd->ch[0] = ch[0];
        nd->ch[1] = ch[1];
        // this impl, double dummy, extern None/Null behave as one node, would be better
        if (p < sm) nd->ch[0] = ch[0] ? ch[0]->add(p, dx, sl, sm) : (new PstNode())->add(p, dx, sl, sm);
        else        nd->ch[1] = ch[1] ? ch[1]->add(p, dx, sm, sr) : (new PstNode())->add(p, dx, sm, sr);
        nd->pull();
        return nd;
    }
    int query(int l, int r, int sl, int sr) {
        if (r <= sl || sr <= l) return 0;
        if (l <= sl && sr <= r) return x;
        int sm = sl + (sr-sl)/2;
        int resl = ch[0] ? ch[0]->query(l, r, sl, sm) : 0;
        int resr = ch[1] ? ch[1]->query(l, r, sm, sr) : 0;
        return resl + resr;
    }

    Ptr add(int p, int dx) {
        return add(p, dx, 0, 1<<17); // 1<<30 AC too
    }
    int query(int l, int r) {
        return query(l, r, 0, 1<<17);
    }
};


const int N = 100005; 
queue<int> q[N];
// merge-seg in based on i as index, query range.
// PST is based on pre as index, since l/r two versions delta(#pre<l) is can taken in l..r
void solve() {
    int n,k;
    cin >> n >> k;
    vector<PstNode*> roots;
    roots.push_back(new PstNode(0));
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        q[x].push(i);
        int pre = 0;
        if ((int)q[x].size() > k) {
            pre = q[x].front(); q[x].pop();
        }
        //cerr<<pre<<','<<i<<endl;
        roots.push_back(roots.back()->add(pre, 1));
    }
    //cerr<<roots[n]->query(0, n)<<endl;
    int res = 0;
    int q; cin >> q;
    while (q--) {
        int l,r;
        cin >> l >> r;
        l = (l+res)%n + 1;
        r = (r+res)%n + 1;
        if (l > r) swap(l, r);
        l--;
        res = roots[r]->query(0, l+1) - l;//roots[l]->query(0, l+1);
        cout << res << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
