from collections import defaultdict
class ListNode(object):
    def __init__(self, v=0, s={''}):
        self.val = v
        self.strings = s
        self.last = None
        self.next = None

class AllOne(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.dic = defaultdict(int)
        listNode = ListNode()
        self.nodes = {0: listNode}
        self.head = listNode
        self.tail = listNode


    def inc(self, key):
        """
        Inserts a new key <Key> with value 1. Or increments an existing key by 1.
        :type key: str
        :rtype: void
        """
        old_val = self.dic[key]
        self.dic[key] += 1
        node = self.nodes[old_val]
        # check if next exists and equals
        if node.next and node.next.val == old_val + 1:
            node.next.strings.add(key)
        else:
            new_node = ListNode(old_val+1, {key})
            self.nodes[old_val+1] = new_node
            new_node.last = node
            new_node.next = node.next
            node.next = new_node
            # check if tail
            if new_node.next:
                new_node.next.last = new_node
            else:
                self.tail = new_node
        # rm from original node
        if old_val != 0:
            node.strings.remove(key)
            if not node.strings:
                node.last.next = node.next
                node.next.last = node.last
                self.nodes.pop(old_val)

    def dec(self, key):
        """
        Decrements an existing key by 1. If Key's value is 1, remove it from the data structure.
        :type key: str
        :rtype: void
        """
        old_val = self.dic[key]
        if old_val == 0:
            return
        self.dic[key] -= 1
        node = self.nodes[old_val]
        if old_val > 1:
            # check last val exits
            if node.last.val == old_val - 1:
                node.last.strings.add(key)
            else:
                new_node = ListNode(old_val-1, {key})
                self.nodes[old_val-1] = new_node
                new_node.last = node.last
                new_node.next = node
                node.last = new_node
                new_node.last.next = new_node
        # rm from node
        node.strings.remove(key)
        if not node.strings:
            node.last.next = node.next
            if node.next:
                node.next.last = node.last
            else:
                self.tail = node.last
            self.nodes.pop(old_val)


    def getMaxKey(self):
        """
        Returns one of the keys with maximal value.
        :rtype: str
        """
        v = self.tail.strings.pop()
        self.tail.strings.add(v)
        return v


    def getMinKey(self):
        """
        Returns one of the keys with Minimal value.
        :rtype: str
        """
        if self.head.next:
            v = self.head.next.strings.pop()
            self.head.next.strings.add(v)
        else:
            v = ''
        return v


# Your AllOne object will be instantiated and called as such:
# obj = AllOne()
# obj.inc(key)
# obj.dec(key)
# param_3 = obj.getMaxKey()
# param_4 = obj.getMinKey()
