import heapq

class Solution(object):
    def getSkyline(self, buildings):
        """
        :type buildings: List[List[int]]
        :rtype: List[List[int]]
        """
        edges = []
        for l, r, h in buildings:
            edges += [(l, -h, r), (r, 1, h)]
        edges.sort()

        skyl = [(0, float('inf'))]
        dots = []
        for x, nh, r in edges:
            last = skyl[0][0]
            if nh > 0:
                while x >= skyl[0][1]:
                    heapq.heappop(skyl)
            else:
                heapq.heappush(skyl, (nh, r))
            if last != skyl[0][0]:
                dots += [[x, -skyl[0][0]]]
        return dots
