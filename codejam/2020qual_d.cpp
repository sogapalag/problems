#include <bits/stdc++.h>

using namespace std;

int B;

int q(int i) {
    cout << i+1 << endl;
    int x; cin >> x;
    return x;
}
void easy() {
    vector<int> a(B/2);
    for (int i = 0; i < B/2; i++) {
        a[i] ^= q(i);
        a[i] ^= q(B-i-1);
    }
    vector<int> res(B);
    for (int i = 0; i < B/2; i++) {
        res[i] = q(i);
        res[B-i-1] = res[i] ^ a[i];
    }
    for (auto& x: res) {
        cout << x;
    }cout << endl;
}
//   00   01
// s 00   10
// f 11   10
//sf 11   01
// so with two pos can decide trans(s, f), every 5x2 as a bucket
void solve() {
    vector<int> a(B/2);
    vector<int> res(B);
    for (int i = 0; i < B/2; i++) {
        a[i] ^= (res[i] = q(i));
        a[i] ^= (res[B-i-1] = q(B-i-1));
    }
    auto flip = [&](int i){
        res[i] ^= 1;
        res[B-i-1] ^= 1;
    };
    auto swp = [&](int i){
        swap(res[i], res[B-i-1]);
    };
    for (int l = 5, r = 10; l < B/2; l+=5, r+=5) {
        int left[2] = {-1, -1};
        int right[2] = {-1, -1};
        for (int i = 0; i < l; i++) {
            left[a[i]] = i;
        }
        for (int i = l; i < r; i++) {
            right[a[i]] = i;
        }
        {
            int s = 0, f = 0;
            if (left[0] == -1) q(0); // dummy
            else {
                int i = left[0];
                f ^= res[i] ^ q(i);
            }
            if (left[1] == -1) q(0); //dummy
            else {
                int i = left[1];
                s ^= f ^ (res[i] ^ q(i));
            }
            if (f) {
                for (int i = 0; i < l; i++) {
                    flip(i);
                }
            }
            if (s) {
                for (int i = 0; i < l; i++) {
                    swp(i);
                }
            }
            //q(0); // dummy
            // 2+3 = 5... here not
        }
        {
            int s = 0, f = 0;
            if (right[0] == -1) q(0); // dummy
            else {
                int i = right[0];
                f ^= res[i] ^ q(i);
            }
            if (right[1] == -1) q(0); //dummy
            else {
                int i = right[1];
                s ^= f ^ (res[i] ^ q(i));
            }
            if (f) {
                for (int i = l; i < r; i++) {
                    flip(i);
                }
            }
            if (s) {
                for (int i = l; i < r; i++) {
                    swp(i);
                }
            }
            q(0); //dummy
        }
    }
    for (auto& x: res) {
        cout << x;
    }cout << endl;
}

// keep in mind what format needed!! might WA!
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T >> B;
    for (int t = 1; t <= T; t++) {
        B <= 20 ? easy() : solve();
        char verdict; cin >> verdict;
        assert(verdict == 'Y');
        //int verdict; cin >> verdict;
        //assert(verdict == 1);
    }
    return 0;
}
