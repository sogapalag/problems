class Solution(object):
    # O(n^2) naive solution, TLE
    def shortestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        for i in reversed(range(len(s))):
            if s[:i+1] == s[i::-1]:
                return s[:i:-1] + s
        return ""
    # approx O(n^2)? but accepted...
    def shortestPalindrome_2(self, s):
        v = s[::-1]
        for i in range(len(s) + 1):
            if s.startswith(v[i:]):
                return v[:i] + s
