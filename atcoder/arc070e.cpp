#include <bits/stdc++.h>

using namespace std;

template <typename Heap>
struct Shifter {
    using T=typename Heap::value_type;

    Heap h;
    T s=0;
    void shift(T x) {
        s += x;
    }
    void push(T x) {
        h.push(x - s);
    }
    T top() {
        return h.top() + s;
    }
    void pop() {
        h.pop();
    }
};
template<class T> using MaxHeap = Shifter<priority_queue<T>>;
template<class T> using MinHeap = Shifter<priority_queue<T, vector<T>, greater<T>>>;

using ll=long long;

// this problem is good. but there're not rigorous proof on web.
// here are some key insight.
// f(x) = dp[i][x], made of slope -i-1, -i,...-1,0,1,...i, i+1 seglines, // induction proof. or draw graph
// let L,R be each half turnning points.
//  note L maintain slope <=0 , R's >= 0
//
// why shift?
// note dp[i][x] = |z-x| + min_{x'~x} dp[i-1][x'], 
//   where x'~x: neither x'+y' < x nor x+y < x' hold. thus min f_{i-1} in  [x-y', x+y]
//   x+y wanna mini, only when in L's. so shift L -y.
//     why res += top-z?. note res = c, i.e. L_top to R-top constant part.
//       so pick x=L_top must be optimal, since |z-x| slope 1, while L's slope all >=1.
//     how to update? push z twice?
//       note update is indeed + g(x)=|z-x|. it will make L'left slope -1 (abs+1), right +1(abs-1). R' all +1.
//       i.e. new L.top moved into R.
void solve() {
    int n; cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        y[i] -= x[i];
    }
    
    MaxHeap<ll> L;
    MinHeap<ll> R;
    L.push(x[0]); R.push(x[0]);
    ll res = 0;
    for (int i = 1; i < n; i++) {
        int z = x[i];
        L.shift(-y[i]);
        R.shift(y[i-1]);
        if (L.top() > z) {
            res += L.top() - z;
            L.push(z); L.push(z);
            R.push(L.top());
            L.pop();
        } else if (z > R.top()) {
            res += z - R.top();
            R.push(z); R.push(z);
            L.push(R.top());
            R.pop();
        } else {
            L.push(z); R.push(z);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
