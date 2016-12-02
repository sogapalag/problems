class Solution(object):
    # O(n)
    def jump(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) <= 1:
            return 0
        # treat 0 as 1, since test work as
        nums = [max(1, e) for e in nums]
        i = 0
        jump = 1
        # nex is most achievable index in jump steps,
        # and 0~nex can achieve in jump steps.
        nex = nums[0]
        while i < len(nums):
            if nex >= len(nums) - 1:
                return jump
            far = nex + 1
            while i <= nex:
                far = max(far, nums[i] + i)
                i += 1
            jump += 1
            nex = far
