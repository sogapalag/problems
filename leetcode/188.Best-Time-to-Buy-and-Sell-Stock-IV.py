import heapq

class Solution(object):
    def maxProfit(self, k, prices):
        """
        :type k: int
        :type prices: List[int]
        :rtype: int
        """
        profits = []
        vps = []
        n = len(prices)
        v, p = 0, 0

        while p < n:
            # local min
            v = p
            while v < n-1 and prices[v] >= prices[v+1]:
                v += 1
            # local max
            p = v + 1
            while p < n and prices[p] >= prices[p-1]:
                p += 1
            # past higher buy price is not attractive any more
            while vps and prices[v] < prices[vps[-1][0]]:
                vv, pp = vps.pop()
                heapq.heappush(profits, -(prices[pp] - prices[vv]))
            # equiv buy-begin sell to the end
            while vps and prices[p-1] >= prices[vps[-1][1]]:
                vv, pp = vps.pop()
                heapq.heappush(profits, -(prices[pp] - prices[v]))
                v = vv

            vps.append((v, p-1))

        # rest transactions
        while vps:
            vv, pp = vps.pop()
            heapq.heappush(profits, -(prices[pp] - prices[vv]))

        # sum up k hightest profits
        res = 0
        k = min(k, n)
        for i in range(k):
            if profits:
                res -= heapq.heappop(profits)
            else:
                break

        return res
