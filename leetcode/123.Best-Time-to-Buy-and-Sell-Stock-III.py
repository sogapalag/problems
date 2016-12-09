class Solution(object):
    def maxProfit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        # essential idea as 188.py
        maxProfit2 = 0
        maxProfit1 = 0
        minBuyPrice2 = 2**32
        minBuyPrice1 = 2**32
        for p in prices:
            maxProfit2 = max(maxProfit2, p - minBuyPrice2)
            minBuyPrice2 = min(minBuyPrice2, p - maxProfit1)
            maxProfit1 = max(maxProfit1, p - minBuyPrice1)
            minBuyPrice1 = min(minBuyPrice1, p)
        return maxProfit2
