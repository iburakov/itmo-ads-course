import functools
from collections import Counter, namedtuple
from queue import PriorityQueue

q = PriorityQueue()
s = input()
n = len(s)


class Node(namedtuple("Node", ["left", "right"])):
    def walk(self, code, acc):
        self.left.walk(code, acc + "0")
        self.right.walk(code, acc + "1")


class Leaf(namedtuple("Leaf", ["char"])):
    def walk(self, code, acc):
        code[self.char] = acc or "0"


@functools.total_ordering
class Entry:
    def __init__(self, freq, node):
        self.freq = freq
        self.node = node

    def __lt__(self, other):
        return self.freq < other.freq

    def __eq__(self, other):
        return self.freq == other.freq

    def tuple(self):
        return self.freq, self.node


for c, freq in Counter(s).items():
    q.put(Entry(freq, Leaf(c)))

while q.qsize() > 1:
    f1, ln = q.get_nowait().tuple()
    f2, rn = q.get().tuple()
    q.put(Entry(f1 + f2, Node(ln, rn)))

_f, root = q.get_nowait().tuple()
code = {}
root.walk(code, "")

encoded = "".join(code[c] for c in s)
print(len(code), len(encoded))
for c in sorted(code):
    print(f"{c}: {code[c]}")
print(encoded)
