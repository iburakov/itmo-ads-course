from collections import Counter

with open("input.txt") as f:
    s = f.read().strip().replace(' ', '')


class Entry:
    left: int
    right: int

    def __init__(self, left=0, right=0):
        self.left = left
        self.right = right

    def __repr__(self):
        return f"L: {self.left}, R: {self.right}"


output = 0
if len(s) >= 3:
    right = {v: Entry(right=right) for v, right in Counter(s).items()}
    left = {}

    cc = s[0]
    ce = right[cc]
    left[cc] = ce
    ce.left += 1
    ce.right -= 1

    output = 0
    for cc in s[1:]:
        ce = right[cc]
        ce.right -= 1

        for k, v in left.items():
            output += v.left * v.right

        ce.left += 1
        left[cc] = ce

with open("output.txt", "w") as f:
    f.write(str(output))

