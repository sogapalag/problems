class Solution(object):
    def palindromePairs(self, words):
        """
        :type words: List[str]
        :rtype: List[List[int]]
        """
        dic = {w: i for i, w in enumerate(words)}
        res = []
        for i, w in enumerate(words):
            for j in range(len(w) + 1):
                lef = w[:j]
                rig = w[j:]
                if lef[::-1] in dic and \
                        dic[lef[::-1]] != i and rig == rig[::-1]:
                    res.append([i, dic[lef[::-1]]])
                if j != 0 and rig[::-1] in dic and \
                        dic[rig[::-1]] != i and lef == lef[::-1]:
                    res.append([dic[rig[::-1]], i])
        return res
