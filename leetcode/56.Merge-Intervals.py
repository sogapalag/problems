# Definition for an interval.
# class Interval(object):
#     def __init__(self, s=0, e=0):
#         self.start = s
#         self.end = e

class Solution(object):
    def merge(self, intervals):
        """
        :type intervals: List[Interval]
        :rtype: List[Interval]
        """
        intervals.sort(key=lambda x: x.start)
        res = []
        empty = True
        n = len(intervals)
        for i, x in enumerate(intervals):
            if empty:
                s = x.start
                e = x.end
                empty = False
            elif x.start <= e:
                e = max(e, x.end)
            else:
                res += Interval(s, e),
                s = x.start
                e = x.end
            # check end
            if i == n-1 and not empty:
                res += Interval(s, e),
        return res

    def merge_short_version(self, intervals):
        res = []
        for x in sorted(intervals, key=lambda x: x.start):
            if res and x.start <= res[-1].end:
                res[-1].end = max(res[-1].end, x.end)
            else:
                res += x,
        return res
