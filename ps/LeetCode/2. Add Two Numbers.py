# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

        
def get_num(head):
    cur = head
    ret = 0
    weight = 1
    while cur is not None:
        ret = weight * cur.val + ret
        cur = cur.next
        weight *= 10
    return ret


def push_front(head, val):
    if head is None:
        head = ListNode(val=val, next=None)
    else:
        next_head = ListNode(val, head)
        head = next_head
    return head


def set_list(n):
    ret = None
    numbers = list(map(int, list(str(n))))
    
    for number in numbers:
        ret = push_front(ret, number)
        
    return ret


class Solution:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        return set_list(get_num(l1) + get_num(l2))
