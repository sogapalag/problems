#include <bits/stdc++.h>

using namespace std;

// https://cp-algorithms.com/string/z-function.html
// https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/zalg.pdf
// note [l,r] is the r-right-most matched z-box
// so z[i-l] used quick back up
// [0..] <-> [l..r]
// [i-l..] ... [i..] implies [i..] match [l..r], thus [i..] match [0..]

// SNIPPETS_START z_fn
// z[i] = len of lcp of s, s[i..]; lcp(longest common prefix)
vector<int> z_fn(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r)
            z[i] = min(r-i+1, z[i-l]);
        while (i+z[i] < n && s[z[i]] == s[i+z[i]]) {
            z[i]++;
        }
        if (i+z[i]-1 > r) {
            l = i; r = i+z[i]-1;
        }
    }
    return z;
}
// SNIPPETS_END

// application
// match, let s = p+'#'+t; calc z(s)
//
// distinct substr, consider process add new char c in start. O(n^2)
// then z(s[i..])' max:= #already occured, thus new str start with c has len(s[i..]) - max
