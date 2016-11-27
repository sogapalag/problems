# O(n^2)
# hint: cut of s[0:i+j] is min 1 + cut of s[0:i-j] when s[i-j:i+j] is palind.
class Solution(object):
    def minCut(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        cut = [0,] * (n+1)
        for i in range(n+1):
            cut[i] = i-1
        for i in range(n):
            # j, delta
            # odd
            j = 0
            while j <= i and i+j < n and s[i-j] == s[i+j]:
                cut[i+1+j] = min(cut[i+1+j], 1 + cut[i-j])
                j += 1
            # even
            j = 0
            while j <= i and i+j+1 < n and s[i-j] == s[i+j+1]:
                cut[i+j+2] = min(cut[i+j+2], 1 + cut[i-j])
                j += 1
        return cut[n]
