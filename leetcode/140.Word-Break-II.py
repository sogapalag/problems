def sharemem(func):
    smem = {}
    def wrapper(*args, **kwargs):
        if args in smem:
            return mem[args]
        r = function(*args, **kwargs)
        smem[args] = r
        return r
    return wrapper

class Solution(object):
    def wordBreak(self, s, wordDict):
        """
        :type s: str
        :type wordDict: Set[str]
        :rtype: List[str]
        """
        mem = {}
        def wordBreak_lis(s):
            if s in mem:
                return mem[s]
            if not len(s):
                return [[]]
            res = []
            for w in wordDict:
                if s.startswith(w):
                    sublis = wordBreak_lis(s[len(w):])
                    for sl in sublis:
                        res.append([w] + sl)
            mem[s] = res
            return res
        return [' '.join(r) for r in wordBreak_lis(s)]

    # 2nd way using decorator
    def wB2(self, s, wordDict):
        @sharemem
        def wB2(s):
            if not len(s):
                return [[]]
            res = []
            for w in wordDict:
                if s.startswith(w):
                    res.extend([[w] + sl for sl in wB2(s[len(w):])]
            return res
        return [' '.join(r) for r in wB2(s)]

