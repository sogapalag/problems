# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

#import numpy as np

class Solution(object):
    def maxPathSum(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        # self.mpath = -np.inf
        # faster
        self.mpath = -2**32
        def dfs(node):
            if not node:
                return 0
            l = dfs(node.left)
            r = dfs(node.right)
            self.mpath = max(self.mpath, l + r + node.val)
            return max(0, l + node.val, r + node.val)
        dfs(root)
        return self.mpath
