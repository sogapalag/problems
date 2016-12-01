class Solution(object):
    def largestRectangleArea(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        stack = [(0, 0)]
        res = 0
        for i, h in enumerate(heights):
            index = i
            # update won't improving rectangle
            while h < stack[-1][1]:
                index, height = stack.pop()
                res = max(res, (i - index) * height)
            if h > stack[-1][1]:
                stack.append((index, h))

        # update rest rectangle.
        n = len(heights)
        while stack:
            index, height = stack.pop()
            res = max(res, (n - index) * height)

        return res
