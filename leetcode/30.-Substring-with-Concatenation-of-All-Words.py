from collections import defaultdict

class Solution(object):
    def findSubstring(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        # test case has same words
        if not words or len(s) < len(words) * len(words[0]):
            return []
        wd = defaultdict(int)
        for w in words:
            wd[w] += 1
        wl, ll, sl = len(words[0]), len(words), len(s)
        res = []
        for i in range(wl):
            start, seri = i, defaultdict(list)
            for j in range(i, sl-wl+1, wl):
                wor = s[j:j+wl]
                if wor in wd:
                    worl = len(seri[wor])
                    # elim <start items
                    for index in range(worl-1, -1, -1):
                        if seri[wor][index] < start:
                            seri[wor].pop()
                        else:
                            break
                    if len(seri[wor]) < wd[wor]:
                        seri[wor].insert(0, j)
                        # match
                        if j - start == wl * (ll-1):
                            res.append(start)
                            start += wl
                    else:
                        start = seri[wor].pop() + wl
                        seri[wor].insert(0, j)
                else:
                    start = j + wl
        return res
