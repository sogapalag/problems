class Solution(object):
    def fullJustify(self, words, maxWidth):
        """
        :type words: List[str]
        :type maxWidth: int
        :rtype: List[str]
        """
        fl = []
        i = 0
        while i < len(words):
            j = i
            total_l = 0
            #space = 0
            while j < len(words):
                if total_l + len(words[j]) + j-i <= maxWidth:
                    total_l += len(words[j])
                else:
                    break
                j += 1
            space = maxWidth - total_l
            # only one word
            if j == i + 1:
                s = words[i] + ' '*space
                fl.append(s)
            # normal
            elif j < len(words):
                rs = space / (j-i-1)
                ls_i = space % (j-i-1)
                s = ''
                for k in range(i, j):
                    s += words[k]
                    if k - i < ls_i:
                        s += ' ' * (rs+1)
                    elif k < j-1:
                        s += ' ' * rs
                fl.append(s)
            # last line
            else:
                s = ''
                for k in range(i, j):
                    s += words[k]
                    if k < j-1:
                        s += ' '
                    else:
                        s += ' ' * (space - (j - i - 1))
                fl.append(s)
            i = j
        return fl

