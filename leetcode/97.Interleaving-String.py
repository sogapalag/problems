class Solution(object):
    def isInterleave(self, s1, s2, s3):
        """
        :type s1: str
        :type s2: str
        :type s3: str
        :rtype: bool
        """
        l1, l2 , l3 = len(s1), len(s2), len(s3)
        if l1 + l2 != l3:
            return False

        # dp[i][j] : s1[:i+1] and s2[:j+1] can form s3[:i+j+1]
        dp = [[False,] * (l2+1) for i in range(l1+1)]
        dp[0][0] = True
        for i in range(1, l3+1):
            j1 = max(0, i-l2)
            while j1 <= min(i, l1):
                if j1-1 >= 0 and s1[j1-1] == s3[i-1]:
                    dp[j1][i-j1] |= dp[j1-1][i-j1]
                if i-j1-1 >= 0 and s2[i-j1-1] == s3[i-1]:
                    dp[j1][i-j1] |= dp[j1][i-j1-1]
                j1 += 1
        return dp[l1][l2]
