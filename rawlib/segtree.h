// !!!! POWERFUL STL
// using ordered_set (policy), i.e. TreeSet, with support order find.
// we just set T pair<int, int>, second be index, then work for repeat first
// then by order find (key, 0/n), we can impl range query.
//
// example method.
// auto it = set.find_by_order(k); //iterator of k-th smallest, (0-based)
// cout << *it;
//
// int k = set.order_of_key(some key T); // #elements strictly less than T
//
// set.erase(key)
//
// example,  map
// template<class key, class value, class cmp = std::less<key>>
// using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;
// ordered_map<int, int> my_map;
//
// example, trie
// typedef trie<string, null_type, trie_string_access_traits<>, pat_trie_tag,trie_prefix_search_node_update> pref_trie;
// trie.insert("string");
// auto rg = trie.prefix_range(key); // range iter. 
// for (auto it = rg.f; it != rg.s; it++) 

//////////////////////////////
//   useful link
////////////////////////////
// Efficient and easy segment trees
// https://codeforces.com/blog/entry/18051
// Algorithm Gym :: Everything About Segment Trees
// https://codeforces.com/blog/entry/15890
// Segment Tree Problems
// https://codeforces.com/blog/entry/22616
// Data Structure
// https://codeforces.com/blog/entry/15729
// C++ STL: Policy based data structures
// https://codeforces.com/blog/entry/11080
// /////////////////////////

#include <bits/stdc++.h>
using namespace std;


/////////////////////////////////
// root is 1, perfect tree; hint: n is not power of 2 also right.
// raw data(leaf) in a[n,...2*n)
// i: parent; 2*i, 2*i+1 children.
//
// classic update-one, query range

const int N = (1<<16) + 5;
int n; // array size
int tr[2 * N];

void build() {
    for (int i = n-1; i >= 1; i--) {
        // or other build rule
        tr[i] = tr[i<<1] + tr[i<<1|1];
    }
}

void upd(int p, int val){
    for (tr[p += n] = val; p > 1; p >>= 1){
        // or other up-date rule, similar build rule.
        tr[p>>1] = tr[p] + tr[p^1];
    }
}

// query [l, r)
int query(int l, int r){
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1){
        if (l & 1)
            res += tr[l++];
        if (r & 1)
            res += tr[--r];
    }
    return res;
}

///////////////////////////////
// range assign, single element access max // ops no effect
//
// e.g. cf/292e  
//
// range assign
void upd(int l, int r, int val){
    for (l += n, r += n; l < r; l >>= 1, r >>= 1){
        if (l & 1)
            tr[l++] = val;
        if (r & 1)
            tr[--r] = val;
    }
}
// max
int query(int p){
    int tmp = 0;
    for (p += n; p > 0; p >>= 1)
        tmp = max(tmp, tr[p]);
    return tmp;
}

//////////////////////////////////////////
//  range add '+', query global max.
//  lazy
//  seg[1], the max.
//
//  e.g. ks/2019b3
const int MX = 1e5+5;
int seg[MX<<2], lzy[MX<<2]; //memset
void split(int _l, int _r, int val, int p=1, int l=0, int r=MX){
    if (_r <= l || r <= _l) return;
    if (_l <= l && r <= _r){
        seg[p] += val;
        lzy[p] += val;
        return;
    }
    int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
    split(_l, _r, val, pl, l, m);
    split(_l, _r, val, pr, m, r);
    seg[p] = max(seg[pl], seg[pr]) + lzy[p];
}

