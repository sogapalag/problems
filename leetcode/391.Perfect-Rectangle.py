import numpy as np
from collections import defaultdict

# O(n)
class Solution(object):
    def isRectangleCover(self, rectangles):
        """
        :type rectangles: List[List[int]]
        :rtype: bool
        """
        blmost = (np.inf, np.inf)
        trmost = (-np.inf, -np.inf)
        total = 0
        point = defaultdict(int)
        for rect in rectangles:
            # total area should be equal
            total += (rect[2]-rect[0]) * (rect[3]-rect[1])
            if rect[0] <= blmost[0] and rect[1] <= blmost[1]:
                blmost = (rect[0], rect[1])
            if rect[2] >= trmost[0] and rect[3] >= trmost[1]:
                trmost = (rect[2], rect[3])
            # corner point is one, else should be even 2 or 4
            point[(rect[0], rect[1])] += 1
            point[(rect[0], rect[3])] += 1
            point[(rect[2], rect[1])] += 1
            point[(rect[2], rect[3])] += 1

        area_equal = total == (trmost[0]-blmost[0]) * (trmost[1]-blmost[1])
        br = (trmost[0], blmost[1])
        tl = (blmost[0], trmost[1])
        if point[br] == point[tl] == point[blmost] == point[trmost] == 1:
            point.pop(br)
            point.pop(tl)
            point.pop(blmost)
            point.pop(trmost)
            valid_point = all(point[e] %2 == 0 for e in point)
        else:
            valid_point = False
        return area_equal and valid_point
