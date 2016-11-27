import heapq

class MedianFinder:
    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.large, self.small = [], []

    def addNum(self, num):
        """
        Adds a num into the data structure.
        :type num: int
        :rtype: void
        """
        heapq.heappush(self.large, num)
        heapq.heappush(self.small, -heapq.heappop(self.large))
        if len(self.large) < len(self.small):
            heapq.heappush(self.large, -heap.heappop(self.small))


    def findMedian(self):
        """
        Returns the median of current data stream
        :rtype: float
        """
        if len(self.large) > len(self.small):
            res = self.large[0]
        else:
            res = (self.large[0] - self.small[0]) / 2.
        return res


# Your MedianFinder object will be instantiated and called as such:
# mf = MedianFinder()
# mf.addNum(1)
# mf.findMedian()
