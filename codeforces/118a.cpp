#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<double,double> pd;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 100001;

char s[111];
char v[12] = {'a', 'o', 'e', 'u', 'y', 'i',
          'A', 'O', 'E', 'U', 'Y', 'I'};

bool vow(char& c){
    F0R(i, 12){
        if (c  == v[i]){
            return true;
        }
    }
    return false;
}

void solve() {
    memset(s, 0, sizeof s);
    cin >> s;
    int i = 0;
    while (s[i]){
        if (!vow(s[i])){
            cout << '.';
            if (s[i] < 'a'){
                cout << (char)(s[i]+32);
            }else{
                cout << s[i];
            }
        }
        i ++;
    }
}

int main() {
    solve();
    cout << endl;
}
