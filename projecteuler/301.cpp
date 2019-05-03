#include <bits/stdc++.h>
using namespace std;

int main(){
    long long N = 1<<30;
    int res = 0;
    for (long long i=1; i<=N; i++){
        if (!(i ^ (i<<1) ^ (i*3)))
            res += 1;
    }
    cout << res << endl;
}
