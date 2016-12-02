class Solution(object):
    def maximalRectangle(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """
        # related to 84.py
        if not matrix:
            return 0
        m, n = len(matrix), len(matrix[0])
        max_area = 0
        for i in range(m):
            stack = [(0, 0)]
            res = 0
            for j in range(n):
                # update height
                matrix[i][j] = (0, 1)[matrix[i][j] == '1']
                if i > 0 and matrix[i][j]:
                    matrix[i][j] += matrix[i-1][j]

                # max area in this level
                index = j
                while matrix[i][j] < stack[-1][1]:
                    index, height = stack.pop()
                    res = max(res, (j - index) * height)
                if matrix[i][j] > stack[-1][1]:
                    stack.append((index, matrix[i][j]))
            # update rest
            while stack:
                index, height = stack.pop()
                res = max(res, (n - index) * height)
            max_area = max(max_area, res)
        return max_area
