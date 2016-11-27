import numpy as np
from collections import defaultdict

class Solution(object):
    def minWindow(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: str
        """
        d = defaultdict(int)
        for c in t:
            d[c] += 1

        begin = end = 0
        count = len(t)
        mins, minl = 0, np.inf
        while end < len(s):
            if d[s[end]] > 0:
                count -= 1
            d[s[end]] -= 1
            end += 1
            # valid
            while count == 0:
                if end - begin < minl:
                    mins = begin
                    minl = end - begin
                d[s[begin]] += 1
                if d[s[begin]] > 0:
                    count += 1
                begin += 1
        return s[mins:mins+minl] if minl != np.inf else ''
