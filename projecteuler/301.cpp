#include <bits/stdc++.h>
using namespace std;

// notice that 3*i = i + (i<<1);
// when '+' don't care carry, '+' is same as ^
// thus result zero, then if carry, means must be nonzero x^0 != 0.
// complete the proof, i is no consective '1'.
//
// let answer f(k) = #valid in (0,1<<k]
// consider i start with '010' or '00',
// => f(k) = 1 + f(k-1) + f(k-2)-1
// => f(k) = f(k-1) + f(k-2), and note f(0)=1,f(0)=2;
// that f(k) is the fibonacci!, f(k) = F(k+2).

// below brute-force, read above.
int main(){
    long long N = 1<<30;
    int res = 0;
    for (long long i=1; i<=N; i++){
        if (!(i ^ (i<<1) ^ (i*3)))
            res += 1;
    }
    cout << res << endl;
}
