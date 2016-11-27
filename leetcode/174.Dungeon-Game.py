import numpy as np

class Solution(object):
    def calculateMinimumHP(self, dungeon):
        """
        :type dungeon: List[List[int]]
        :rtype: int
        """
        m, n = len(dungeon), len(dungeon[0])
        for diag in range(m+n-2, -1, -1):
            i = min(m - 1, diag)
            while i >= 0 and diag - i < n:
                down = dungeon[i+1][diag-i] if i+1 < m else np.inf
                right = dungeon[i][diag-i+1] if diag-i+1 < n else np.inf
                if diag == m+n-2:
                    down = right = 1
                cost = dungeon[i][diag-i]
                dungeon[i][diag-i] = max(1, min(down, right) - cost)
                i -= 1
        return dungeon[0][0]
