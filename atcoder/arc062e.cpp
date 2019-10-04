#include <bits/stdc++.h>

using namespace std;

#define rep(i) for(int i=0;i<4;i++)
using ll=long long;
using Token=array<int,4>;
// min lexi
void norm(Token& t){
    Token res = t;
    rep(_){
        Token sft = {t[(1+_)%4],t[(2+_)%4],t[(3+_)%4],t[_]};
        res = min(res, sft);
    }
    t = res;
}
// 1 1 := 4   1 2 := 2
// 1 1        2 1 
ll repeat(const Token& t) {
    if (t[0] != t[2]) return 1;
    if (t[1] != t[3]) return 1;
    return t[0]==t[1]?4:2;
}
void solve() {
    int n; cin >> n;
    vector<Token> a(n);
    map<Token, ll> cnt;
    for (int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3];
        norm(a[i]);
        cnt[a[i]]++;
    }
    ll res = 0;
    //     j:1+k 0+k
    //    /  2+k 3+k
    //   /
    // i: 0 1
    //    3 2
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            rep(k){
                Token U = {a[j][(1+k)%4], a[j][(0+k)%4], a[i][1], a[i][0]}; norm(U);
                Token R = {a[i][1], a[j][(0+k)%4], a[j][(3+k)%4], a[i][2]}; norm(R);
                Token D = {a[i][2], a[j][(3+k)%4], a[j][(2+k)%4], a[i][3]}; norm(D);
                Token L = {a[j][(1+k)%4], a[i][0], a[i][3], a[j][(2+k)%4]}; norm(L);
                ll tmp = 1;
                ll d = cnt[U] - (a[i]==U) - (a[j]==U);
                tmp *= d>0?d:0;
                d = cnt[R] - (a[i]==R) - (a[j]==R) - (U==R);
                tmp *= d>0?d:0;
                d = cnt[D] - (a[i]==D) - (a[j]==D) - (U==D) - (R==D);
                tmp *= d>0?d:0;
                d = cnt[L] - (a[i]==L) - (a[j]==L) - (U==L) - (R==L) - (D==L);
                tmp *= d>0?d:0;
                tmp *= repeat(U);
                tmp *= repeat(R);
                tmp *= repeat(D);
                tmp *= repeat(L);
                res += tmp;
            }
        }
    }
    res /= 3;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
