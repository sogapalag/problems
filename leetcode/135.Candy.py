class Solution(object):
    def candy_2(self, ratings):
        """
        :type ratings: List[int]
        :rtype: int
        """
        n = len(ratings)
        cdy = [1,] * n
        # climb from left -> right
        v, p = 0, 0
        while p < n:
            # local min
            v = p
            while v < n-1 and ratings[v] >= ratings[v+1]:
                v += 1
            # local max
            p = v + 1
            while p < n and ratings[p] > ratings[p-1]:
                cdy[p] = max(cdy[p], 1 + cdy[p-1])
                p += 1
        # climb from right -> left
        v, p = n-1, n-1
        while p >= 0:
            v = p
            while v > 0 and ratings[v] >= ratings[v-1]:
                v -= 1
            p = v - 1
            while p >= 0 and ratings[p] > ratings[p+1]:
                cdy[p] = max(cdy[p], 1 + cdy[p+1])
                p -= 1
        return sum(cdy)

    # shorter version, not care local
    def candy(self, ratings):
        n = len(ratings)
        cdy = [1,] * n
        for i in range(1, n):
            if ratings[i] > ratings[i-1]:
                cdy[i] = 1 + cdy[i-1]
        for i in reversed(range(n-1)):
            if ratings[i] > ratings[i+1]:
                cdy[i] = max(cdy[i], 1 + cdy[i+1])
        return sum(cdy)
