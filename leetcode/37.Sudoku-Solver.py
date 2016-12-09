from copy import deepcopy

class Solution(object):
    def solveSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: void Do not return anything, modify board in-place instead.
        """
        valid = set(str(i) for i in range(1, 10))
        # remain in row, column, square in #i
        rem = {}
        for i in range(9):
            rem[('r', i)] = deepcopy(valid)
            rem[('c', i)] = deepcopy(valid)
            rem[('s', i)] = deepcopy(valid)
        spot = lambda i,j: (i, j, i//3 * 3 + j//3)
        for i in range(9):
            for j in range(9):
                if board[i][j] != '.':
                    r, c, s = spot(i, j)
                    rem[('r', r)].remove(board[i][j])
                    rem[('c', c)].remove(board[i][j])
                    rem[('s', s)].remove(board[i][j])
        # possible
        pos = {}
        #unfinished = set()
        for i in range(9):
            for j in range(9):
                if board[i][j] == '.':
                    r, c, s = spot(i, j)
                    #unfinished.add((i, j))
                    pos[(i, j)] = rem[('r', r)] & rem[('c', c)] & rem[('s', s)]
        def solve(pos, board):
            if not pos:
                return True
            lstk = None
            minl = 10
            ch = '.'
            for k, v in pos.items():
                if len(v) == 1:
                    lstk = k
                    ch = v.pop()
                    break
                # exclude
                r, c, s = spot(k[0], k[1])
                # row
                exc = deepcopy(v)
                for i in range(9):
                    if (r, i) != k and (r, i) in pos:
                        exc -= pos[(r, i)]
                if len(exc) == 1:
                    lstk = k
                    ch = exc.pop()
                    break
                # column
                exc = deepcopy(v)
                for i in range(9):
                    if (i, c) != k and (i, c) in pos:
                        exc -= pos[(i, c)]
                if len(exc) == 1:
                    lstk = k
                    ch = exc.pop()
                    break
                # square
                rr, cc = r - r%3, c - c%3
                exc = deepcopy(v)
                for i in range(3):
                    for j in range(3):
                        if (rr+i, cc+j) != k and (rr+i, cc+j) in pos:
                            exc -= pos[(rr+i, cc+j)]
                if len(exc) == 1:
                    lstk = k
                    ch = exc.pop()
                    break
                # update min possible lenth
                if len(v) < minl:
                    lstk = k
                    minl = len(v)
                    if minl == 0:
                        return False

            old_pos = None
            old_board = None
            if ch == '.':
                ch = pos[lstk].pop()
                old_pos = deepcopy(pos)
                old_board = deepcopy(board)
            # update pos
            board[lstk[0]][lstk[1]] = ch
            pos.pop(lstk)
            r, c, s = spot(lstk[0], lstk[1])
            for i in range(9):
                if (r, i) in pos:
                    pos[(r, i)] -= {ch}
            for i in range(9):
                if (i, c) in pos:
                    pos[(i, c)] -= {ch}
            rr, cc = r - r%3, c - c%3
            for i in range(3):
                for j in range(3):
                    if (rr+i, cc+j) in pos:
                        pos[(rr+i, cc+j)] -= {ch}
            # recover
            if not solve(pos, board):
                if not old_pos or not old_board:
                    return False
                pos = deepcopy(old_pos)
                # board addr cannot change
                # board = deepcopy(old_board)
                for i in range(9):
                    for j in range(9):
                        board[i][j] = old_board[i][j]
                return solve(pos, board)
            return True


        solve(pos, board)


