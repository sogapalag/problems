# source: https://discuss.leetcode.com/topic/32298/short-python-ruby-c
class Solution(object):
    def maxNumber(self, nums1, nums2, k):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k: int
        :rtype: List[int]
        """
        def prep(nums, k):
            # max #could be remv
            remv = len(nums) - k
            out = []
            for dig in nums:
                while remv and out and out[-1] < dig:
                    out.pop()
                    remv -= 1
                out.append(dig)
            return out[:k]

        def merge(a, b):
            return [max(a, b).pop(0) for _ in a+b]

        res = []
        for i in range(k+1):
            if i <= len(nums1) and k-i <= len(nums2):
                res = max(res, merge(prep(nums1, i), prep(nums2, k-i)))
        return res
