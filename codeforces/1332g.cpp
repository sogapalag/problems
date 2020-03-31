#include <bits/stdc++.h>

using namespace std;

// draw some case, can note answer<=4, the hard part is how to impl find suitable
// 4:  /\     #
//       \/   #
// the ends strictly inside mi..mx
// key: first element neither exist in mx/mi stack is right-end
void solve() {
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    
    vector<int> mx, mi;
    vector<int> occur(n, 2);
    set<int> absent; absent.insert(n+1);
    vector<array<int,4>> four(n);
    vector<array<int,3>> three(n);
    vector<int> r4(n, n+1), r3(n, n+1);
    auto les = [&](int x, int y){
        return a[x] < a[y];
    };
    auto grt = [&](int x, int y){
        return a[x] > a[y];
    };
    // for each i as end, find its valid right end
    for (int i = n-1, dec_len = 0, inc_len = 0; i >= 0; i--) {
        while (!mi.empty() && les(i, mi.back())) {
            if (!--occur[mi.back()]) absent.insert(mi.back());
            dec_len = 0;
            mi.pop_back();
        }
        while (!mx.empty() && grt(i, mx.back())) {
            if (!--occur[mx.back()]) absent.insert(mx.back());
            inc_len = 0;
            mx.pop_back();
        }
        // 4
        // the pos can make i inside
        // i.e. mi[it] < val[i] < mx[jt]
        auto it = lower_bound(mi.begin(), mi.end(), i, les) - mi.begin();
        auto jt = lower_bound(mx.begin(), mx.end(), i, grt) - mx.begin();
        it--;jt--;
        if (it>=0 && jt>=0) {
            // right inside
            r4[i] = *absent.lower_bound(max(mi[it], mx[jt]));
            if (r4[i] < n) {
                int x = *lower_bound(mi.begin(), mi.end(), r4[i], greater<int>());
                int y = *lower_bound(mx.begin(), mx.end(), r4[i], greater<int>());
                assert(x != y);
                if (x > y) swap(x, y);
                four[i] = {i, x, y, r4[i]};
            }
        }
        // suffix best
        if (i+1<n && r4[i] > r4[i+1]) {
            r4[i] = r4[i+1];
            four[i] = four[i+1];
        }
        // 3
        // (noninc)dec_len: from i..
        r3[i] = i + max(dec_len, inc_len) + 1;
        three[i] = {i, r3[i]-1, r3[i]};
        if (i+1<n && r3[i] > r3[i+1]) {
            r3[i] = r3[i+1];
            three[i] = three[i+1];
        }

        dec_len++;
        inc_len++;
        mi.push_back(i);
        mx.push_back(i);
    }
    while (q--) {
        int x, y;
        cin >> x >> y;
        x--;
        if (r4[x] < y) {
            cout << "4\n";
            for (int i:four[x]) {
                cout << i+1 << ' ';
            }cout << '\n';
        } else if (r3[x] < y) {
            cout << "3\n";
            for (int i:three[x]) {
                cout << i+1 << ' ';
            }cout << '\n';
        } else cout << "0\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
