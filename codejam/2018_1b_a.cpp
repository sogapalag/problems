#include <bits/stdc++.h>

using namespace std;


// WA. should 1by1, x->x' could still > y
void __solve() {
    int S, n;
    cin >> S >> n;
    int h = (S+1)/2;
    int base = 0;
    vector<int> a;
    int rem = S;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        rem -= x;
        x *= 100;
        int k = x/S, r = x%S;
        if (r*2 >= S) {
            ++k;
        } else {
            a.push_back(r);
        }
        base += k;
    }
    for (int _ = 0; _ < S; _++) {//S not n
        a.push_back(0);
    }
    sort(a.begin(), a.end(), greater<int>());
    int res = base;
    for (int x: a) {
        int need = (h-x+99)/100;
        if (rem < need) break;
        rem -= need; 
        x += need*100;
        res += x/S;
        x %= S;
        if (x*2 >= S) res++;
    }
    int x = rem*100;
    res += x/S;
    x%=S;
    if (x*2 >= S) res++;
    cout << res << "\n";
}

void solve() {
    int S, n;
    cin >> S >> n;
    int H = (S+1)/2;
    int rem = S;
    priority_queue<int> pq;
    int res = 0;
    auto calc = [&](int x){
        res += x/S; x%=S;
        if (x >= H) {
            ++res;
        } else {
            pq.push(x);
        }
    };
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        rem -= x;
        x *= 100;
        calc(x);
    }
    for (int _ = 0; _ < S; _++) {
        pq.push(0);
    }
    for (int _ = 0; _ < rem; _++) {
        int x = pq.top(); pq.pop();
        calc(x + 100);
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
