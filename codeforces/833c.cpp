#include <bits/stdc++.h>

using namespace std;

int l[19], r[19], a[19];
int cnt[10], f[10], buf[10];
int res = 0;

bool ck() {
    int i = 0;
    for (; i < 19; i++) {
        if (l[i]==r[i]) {
            a[i] = l[i];
            if (f[a[i]] > 0) f[a[i]]--;
            else return false;
        } else break;
    }
    if (i == 19) return true;
    // has < x <
    for (int x = l[i]+1; x < r[i]; x++) {
        if (f[x] > 0) return true;
    }
    memcpy(buf, f, sizeof buf);
    int oi = i;
    // l=x<r, rest dec.
    if (f[l[i]] > 0) {
        a[i] = l[i]; f[l[i]]--;
        i++;
        for (int x = 9; x >= 0; x--) {
            while (f[x] > 0) {
                a[i] = x;
                f[x]--;
                if (a[i] > l[i]) return true;
                if (a[i] < l[i]) goto nxt;
                i++;
            }
        }
        return true;
    }
nxt:;
    swap(f, buf);
    i = oi;
    // l<x=r, rest inc.
    if (f[r[i]] > 0) {
        a[i] = r[i]; f[r[i]]--;
        i++;
        for (int x = 0; x <= 9; x++) {
            while (f[x] > 0) {
                a[i] = x;
                f[x]--;
                if (a[i] < r[i]) return true;
                if (a[i] > r[i]) return false;
                i++;
            }
        }
        return true;
    }
    return false;
}

void gen(int d, int len) {
    if (d > 0) {
        for (int i = 0; i <= len; i++) {
            cnt[d] = i;
            gen(d-1, len - i);
        }
    } else {
        cnt[0] = len;
        memcpy(f, cnt, sizeof f);
        //if (ck()) {
        //    for (int x = 0; x < 10; x++) {
        //        cout << cnt[x] << ' ';
        //    }cout << '\n';
        //}
        res += ck();
    }
}

void solve() {
    string L, R;
    cin >> L >> R;
    int n = L.size();
    for (int i = n-1, k=18; i >= 0; i--,k--) {
        l[k] = L[i]-'0';
    }
    n = R.size();
    for (int i = n-1, k=18; i >= 0; i--,k--) {
        r[k] = R[i]-'0';
    }
    //for (int i = 0; i < 19; i++) {
    //    cout << l[i];
    //}cout << '\n';
    //for (int i = 0; i < 19; i++) {
    //    cout << r[i];
    //}cout << '\n';
    gen(9, 19);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
