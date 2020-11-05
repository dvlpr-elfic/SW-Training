
import sys
sys.setrecursionlimit(10**6)

class Node:
    def __init__(self, n=0, x=0, y=0, left=None, right=None):
        self.n = n
        self.x = x
        self.y = y
        self.left = left
        self.right = right
        return None

def make_nodes(nodeinfo):
    for i in range(len(nodeinfo)):
        n = i + 1
        nodeinfo[i].append(n)
    nodeinfo.sort(key=lambda x:(-x[1], x[0]))
    return nodeinfo

def tree_push(root, info):
    x, y, n = info
    if root is None:
        root = Node(n, x, y, None, None)
        return root
    newnode = Node(n, x, y, None, None)
    parent = root
    while True:
        if parent.x > x:
            if parent.left is None:
                parent.left = newnode
                break
            else:
                parent = parent.left
                continue
        else:
            if parent.right is None:
                parent.right = newnode
                break
            else:
                parent = parent.right
                continue
    return root

def preorder(cur, path):
    if cur is None:
        return None
    path.append(cur.n)
    preorder(cur.left, path)
    preorder(cur.right, path)
    return None

def postorder(cur, path):
    if cur is None:
        return None
    postorder(cur.left, path)
    postorder(cur.right, path)
    path.append(cur.n)
    return None

def make_tree(nodes):
    root = None
    for node in nodes:
        x, y, n = node
        root = tree_push(root, (x, y, n))
    return root

def solution(nodeinfo):
    answer = []
    nodes = make_nodes(nodeinfo)
    root = make_tree(nodes)
    path = []
    preorder(root, path)
    answer.append(path)
    path = []
    postorder(root, path)
    answer.append(path)
    return answer
