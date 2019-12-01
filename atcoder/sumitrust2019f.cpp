#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    ll T1, T2;
    ll A1, A2;
    ll B1, B2;
    cin >> T1 >> T2;
    cin >> A1 >> A2;
    cin >> B1 >> B2;
    ll SA = A1*T1 + A2*T2;
    ll SB = B1*T1 + B2*T2;
    if (SA == SB) {
        cout << "infinity"; return;
    }
    if (SA > SB) {
        swap(A1, B1);
        swap(A2, B2);
        swap(SA, SB);
    }

    ll res = 0;
    {// every A catch B, correspoding B catch back, since SB > SA
     // since t=0 not counted, so 2*k+1
     // but if % = 0, res--, since A catch B after dt=0, B catch A.
        ll D = A1 - B1;
        //cout << A1 << "\n";
        if (D > 0) {
            res += D*T1/(SB-SA);
            res *= 2;
            res++;
            if ((D*T1) % (SB-SA) == 0) res--;
        }
    }
    //{
    //    ll D = A2 - B2;
    //    ll X = T2 * D - (B1*T1 - A1*T1);
    //    //cout << X << "\n";
    //    if (X > 0) {
    //        res += X / (SB-SA);
    //        //cout << res << "\n";
    //    }
    //}
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
