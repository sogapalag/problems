#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START compress
template <typename T=int>
struct Compress {
    map<T, int> id;
    vector<T> num;

    inline int get_id(T x) {
        if (!id.count(x)) {
            id[x] = num.size();
            num.emplace_back(x);
        }
        return id[x];
    }
    inline T get_num(int i) {
        assert(0 <= i && i < num.size());
        return num[i];
    }
};
// SNIPPETS_END
