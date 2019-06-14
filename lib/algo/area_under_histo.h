#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START histo
// make sure data in d[1..=n], and >= 0.
template <typename T=int>
T max_area(const vector<T>& d, int n=0) {
    if (!n) n = d.size() - 2;
    assert(n > 0 && d[0] == 0 && d[n+1] == 0);
    vector<int> stk; stk.reserve(n+2);
    stk.emplace_back(0);
    T res = 0;
    for (int i = 1; i <= n+1; i++) {
        while (d[i] < d[stk.back()]) {
            T ht = d[stk.back()]; stk.pop_back();
            T tmp = ht * (i - stk.back() - 1);
            res = max(res, tmp);
        }
        stk.emplace_back(i);
    }
    return res;
}
// SNIPPETS_END

void solve() {
int n = 100;
vector<int> d(n+2);
d[0] = d[n+1] = 0;
auto mx_area = [&](){
    int res = 0;
    vector<int> stk; stk.reserve(n+2);
    stk.emplace_back(0);
    for (int i = 1; i <= n+1; i++) {
        while (d[i] < d[stk.back()]) {
            int ht = d[stk.back()]; stk.pop_back();
            int tmp = ht * (i - stk.back() - 1);
            res = max(res, tmp);
        }
        stk.emplace_back(i);
    }
    return res;
};
mx_area();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
