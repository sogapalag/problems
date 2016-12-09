from collections import defaultdict

class Solution(object):
    def isScramble(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        """
        def cmp(s1, s2):
            d = defaultdict(int)
            for c in s1:
                d[c] += 1
            for c in s2:
                d[c] -= 1
            return all(v == 0 for v in d.values())

        def solve(s1, s2):
            if s1 == s2:
                return True
            if cmp(s1, s2):
                n = len(s1)
                for i in range(1, n):
                    if solve(s1[:i], s2[:i]) and solve(s1[i:], s2[i:]):
                        return True
                    if solve(s1[:i], s2[n-i:]) and solve(s1[i:], s2[:n-i]):
                        return True
                return False
            return False

        return solve(s1, s2)
