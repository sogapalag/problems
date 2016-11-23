# Greedy is correct since *XX* will match XX--XX both correct.
class Solution(object):
    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        s_i = p_i = 0
        bt = 0
        star = -1
        while s_i < len(s):
            if p_i < len(p) and (s[s_i] == p[p_i] or p[p_i] == '?'):
                s_i += 1
                p_i += 1
            elif p_i < len(p) and p[p_i] == '*':
                bt = s_i
                star = p_i
                p_i += 1
            elif star != -1:
                p_i = star + 1
                bt += 1
                s_i = bt
            else:
                return False
        while p_i < len(p) and p[p_i] == '*':
            p_i += 1
        return p_i == len(p)
