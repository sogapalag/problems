# source https://discuss.leetcode.com/topic/64462/c-python-0ms-o-log-n-2-time-o-1-space-super-easy-solution-with-detailed-explanations
class Solution(object):
    def findKthNumber(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """
        # search prefix as res
        res = 1
        k -= 1
        while k > 0:
            count = 0
            interval = [res, res+1]
            while interval[0] <= n:
                count += (min(n+1, interval[1]) - interval[0])
                interval = [10*interval[0], 10*interval[1]]

            if k >= count:
                res += 1
                k -= count
            else:
                res *= 10
                k -= 1
        return res
