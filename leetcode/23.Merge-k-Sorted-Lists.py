# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None
import heapq

class Solution(object):
    def mergeKLists(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        minheap = []
        for i, node in enumerate(lists):
            if node:
                heapq.heappush(minheap, (node.val, i))
        head = ListNode()
        node = head
        while minheap:
            v, i = heapq.heappop(minheap)
            node.next = lists[i]
            node = node.next
            lists[i] = lists[i].next
            if lists[i]:
                heapq.heappush(minheap, (lists[i].val, i))
        return head.next
