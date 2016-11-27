class Solution(object):
    def longestValidParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """
        res = 0
        left = -1
        stack = []
        for i, c in enumerate(s):
            if c == '(':
                stack.append(i)
            else:
                if not stack:
                    left = i
                else:
                    stack.pop()
                    if not stack:
                        res = max(res, i - left)
                    else:
                        res = max(res, i - stack[-1])
        return res
