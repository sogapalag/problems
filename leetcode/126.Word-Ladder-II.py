# TLE
class Solution(object):
    def findLadders(self, beginWord, endWord, wordlist):
        """
        :type beginWord: str
        :type endWord: str
        :type wordlist: Set[str]
        :rtype: List[List[int]]
        """
        bw = beginWord
        ew = endWord
        visit = set()
        unvisit = set(wordlist)
        maxlevel = len(wordlist)+1
        path = [[bw]]
        visit |= {bw}
        unvisit -= {bw}
        unvisit |= {ew}
        level = 0
        while level < maxlevel and path:
            wl = set()
            print(level, path)
            for i in range(len(path)):
                for w in unvisit:
                    if self.adj(path[0][-1], w):
                        path.append(path[0][:]+[w])
                        wl.add(w)
                        if w==ew:
                            maxlevel = level
                path.pop(0)
            visit |= wl
            unvisit -= wl
            level += 1
        print(path)
        path = list(filter(lambda e: e[-1]==ew, path))
        print(path)
        return path
    def adj(self, hit, hot):
        dif = 0
        for i in range(len(hit)):
            if hit[i]!=hot[i]:
                dif += 1
            if dif>1:
                return False
        return True if dif==1 else False
bw = 'hit'
ew = 'cog'
wlis = ['hot', 'dot', 'dog', 'lot', 'log']
Solution().findLadders(bw, ew, wlis)
