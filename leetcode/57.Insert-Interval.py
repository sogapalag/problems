# Definition for an interval.
# class Interval(object):
#     def __init__(self, s=0, e=0):
#         self.start = s
#         self.end = e

class Solution(object):
    def insert(self, intervals, newInterval):
        """
        :type intervals: List[Interval]
        :type newInterval: Interval
        :rtype: List[Interval]
        """
        n = len(intervals)

        # find intersect interval left&right
        left = 0
        while left < n and intervals[left].end < newInterval.start:
            left += 1
        right = left
        while right < n and intervals[right].start <= newInterval.end:
            right += 1

        # update intervals
        if left == right:
            intervals.insert(left, newInterval)
            return intervals
        s = min(newInterval.start, intervals[left].start)
        e = max(newInterval.end, intervals[right-1].end)
        return intervals[:left] + [Interval(s,e)] + intervals[right:]
