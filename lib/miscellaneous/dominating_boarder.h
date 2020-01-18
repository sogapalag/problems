#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START dominating_boarder
// should hold transitivity.
using PartialOrd = function<bool(int,int)>;
// f(x, i): x by(<) i
vector<int> get_dominating_left(int n, PartialOrd f) {
    assert(n > 0);
    vector<int> L(n);
    vector<int> stk;
    for (int i = 0; i < n; i++) {
        // some case might need check dominating itself here
        // if not dominating itself, L[i] = i + 1;
        while (!stk.empty() && f(stk.back(), i)) {
            stk.pop_back();
        }
        L[i] = stk.empty() ? 0 : stk.back() + 1;
        stk.push_back(i);
    }
    return L;
}
vector<int> get_dominating_right(int n, PartialOrd f) {
    assert(n > 0);
    vector<int> R(n);
    vector<int> stk;
    for (int i = n-1; i >= 0; i--) {
        // if not dominating itself, R[i] = i - 1;
        while (!stk.empty() && f(stk.back(), i)) {
            stk.pop_back();
        }
        R[i] = stk.empty() ? n-1 : stk.back() - 1;
        stk.push_back(i);
    }
    return R;
}
// SNIPPETS_END
