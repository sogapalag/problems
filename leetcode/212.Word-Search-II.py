class Solution(object):
    def findWords(self, board, words):
        """
        :type board: List[List[str]]
        :type words: List[str]
        :rtype: List[str]
        """
        def buildTrie(words):
            trie = {}
            for w in words:
                node = trie
                for c in w:
                    if c not in node:
                        node[c] = {}
                    node = node[c]
                node['#'] = w
            return trie

        def dfs(i, j, trie, res):
            if '#' in trie:
                res.add(trie['#'])

            if not 0<=i<len(board) or \
               not 0<=j<len(board[0]) or \
               board[i][j] not in trie:
                return

            c = board[i][j]
            board[i][j] = '*'

            for di, dj in zip((-1, 1, 0, 0), (0, 0, -1, 1)):
                dfs(i+di, j+dj, trie[c], res)
            board[i][j] = c

        trie = buildTrie(words)
        res = set()
        for i in range(len(board)):
            for j in range(len(board[0])):
                dfs(i, j, trie, res)
        return list(res)

