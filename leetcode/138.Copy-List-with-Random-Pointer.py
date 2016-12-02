# Definition for singly-linked list with a random pointer.
# class RandomListNode(object):
#     def __init__(self, x):
#         self.label = x
#         self.next = None
#         self.random = None

class Solution(object):
    def copyRandomList(self, head):
        """
        :type head: RandomListNode
        :rtype: RandomListNode
        """
        if not head:
            return None
        ranlis = []
        i = 0
        node = head
        while node:
            ranlis += RandomListNode(node.label),
            node.id = i
            node = node.next
            i += 1
        node = head
        i = 0
        while node:
            if node.next:
                ranlis[i].next = ranlis[i+1]
            if node.random:
                ranlis[i].random = ranlis[node.random.id]
            node = node.next
            i += 1
        return ranlis[0]
