#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;
typedef vector<pi> vpi;
#define mp make_pair
#define pb push_back

const int N = 1e6+5;
bool prime[N];
// for large n, e.g. 1e9, keep [0..sqrt(n)]
// [0..n], O(n) space, O(nlogn)time
// 45000^2  <(~)  1 << 31
void sieve(int n=45000){
    memset(prime, true, sizeof prime);
    prime[0] = false; prime[1] = false;
    for (int p=2; p*p <= n; p++){
        if (prime[p]){
            for (int i=p*p; i <= n; i += p){
                prime[i] = false;
            }
        }
    }
}

// if for small num, can use a modified sieve, 2=s[2]=s[4]=s[6]...instead bool
// thus a O(log n) time
// for large, below
// num>1, e.g. 150 => (2, 1), (3, 1), (5, 2)
vpi decomp(int num){
    vpi be;
    for (int p=2; p*p <= num && num > 1; p++){
        if (prime[p]){
            int exp = 0;
            while (num % p == 0){
                exp += 1;
                num /= p;
            }
            if (exp != 0){
                be.pb(mp(p, exp));
            }
        }
    }
    if (num != 1){
        be.pb(mp(num, 1));
    }
    return be;
}

