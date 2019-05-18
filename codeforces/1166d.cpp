#include <bits/stdc++.h>

using namespace std;


void solve() {
    long long a, b, m;
    cin >> a >> b >> m;
    if (a > b) {
        cout << "-1\n";
        return;
    }
    if (a == b) {
        cout << "1 " << a << "\n";
        return;
    }
    const int N = 51; 
    for (int i = 2; i < N; i++) {
        long long co = 1ll << (i-2);
        if (b < (a+1)*co) {
            cout << "-1\n";
            return;
        }
        if (b <= (a+m)*co) {
            cout << i << ' ';
            long long l = 1, r = m+1;
            long long mid;
            while (l != r){
                mid = (l+r)>>1;
                if ((a+mid)*co <= b) {
                    l = mid+1;
                }else{
                    r = mid;
                }
            }
            long long k = r-1;
            assert(k > 0);
            long long rem = b - (a+k)*co;
            vector<long long> res(i);
            res[0] = a; res[i-1] = b;
            int crt = 0;
            for (int j = i-2; j >= 1; j--) {
                int u = i-2-j;
                int nxt = (rem>>u)&1;
                res[j] = (res[j+1] + nxt - crt)>>1;
                crt = nxt;
            }
            assert(a+k+crt == res[1]);
            for (auto& x: res) {
                cout << x << ' ';
            }
            cout << '\n';
            return;
        }
    }
    assert(false);
}

// note r_{j} = k + rem_{i-j-1}
// x_n = 2x_{n-1} + r_n - r_{n-1} = 2x_{n-1} + rem_-1(=0) - rem_{0}
// ....
// x_n = 2^j (2x_{n-j} - rem_{j-1}) + rem_-1(=0) + 1*(rem_0) +2 ..+2^{j-1} (rem_{j-2})
// thus x_n>>j, right(outside braket) must to zero.
// then whatever rem_{j-1}. plus 1, then >>1 must equal to x_{n-j}. QED.
void solve2() {
    long long a, b, m;
    cin >> a >> b >> m;
    if (a > b) {
        cout << "-1\n";
        return;
    }
    if (a == b) {
        cout << "1 " << a << "\n";
        return;
    }
    const int N = 51; 
    for (int i = 2; i < N; i++) {
        long long co = 1ll << (i-2);
        if (b < (a+1)*co) {
            cout << "-1\n";
            return;
        }
        if (b <= (a+m)*co) {
            cout << i << ' ';
            cout << a << ' ';
            for (int j = 2; j <= i-1; j++) {
                long long x = ((b>>(i-j-1))+1)>>1;
                cout << x << ' ';
            }
            cout << b << '\n';
            return;
        }
    }
    assert(false);

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        solve2();
    }
    cout << endl;
}
