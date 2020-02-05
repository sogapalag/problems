#include "../ds/seglazy_range_add_global_max.h"

// ensure y fit in 1e6 range
// find max of which point being most covered. on side included.
struct MaxRectangleCover {
    using X = int;
    struct Event {
        X x; int yl, yr;
        int val;
        Event() {}
        Event(X _x, int _yl, int _yr, int _val) : x(_x), yl(_yl), yr(_yr), val(_val) {}
        bool operator<(const Event& _oth) const {
            return x < _oth.x;
        }
    };
    vector<Event> evs;
    int min_y, max_y;
    MaxRectangleCover() : min_y(1e8), max_y(-1) {}

    // [)
    void add_rect(X xl, int yl, X xr, int yr) {
        min_y = min(min_y, yl);
        max_y = max(max_y, yr);
        evs.emplace_back(xl, yl, yr, +1);
        evs.emplace_back(xr, yl, yr, -1);
    }

    int solve() {
        assert(0 <= min_y && min_y < max_y && max_y <= 1000006);// set limit
        sort(evs.begin(), evs.end());
        RangeAddGlobalMax s(max_y);
        int res = 0;
        int n = evs.size();
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && evs[j].x == evs[i].x) {
                s.add(evs[j].yl, evs[j].yr, evs[j].val);
                j++;
            }
            res = max(res, s.get_max());
            i = j;
        }
        return res;
    }
};
