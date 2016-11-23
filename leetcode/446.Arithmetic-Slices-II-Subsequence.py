from collections import defaultdict

class Solution(object):
    def numberOfArithmeticSlices(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        # dp[i][step]: ending at i, step is step
        dp = [defaultdict(int) for i in range(len(A))]
        total = 0
        for i in range(len(A)):
            for j in range(i):
                step = A[i] - A[j]
                dp[i][step] += 1
                if step in dp[j]:
                    dp[i][step] += dp[j][step]
                    total += dp[j][step]
        return total
