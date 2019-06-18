heap = ['_']


def swap(i1, i2):
    heap[i1], heap[i2] = heap[i2], heap[i1]


n = int(input())

for i in range(n):
    inp = input().split()
    cmd = inp[0]
    if cmd == "Insert":
        arg = int(inp[1])

        heap.append(arg)
        ni = len(heap) - 1
        while ni // 2 and heap[ni // 2] < arg:
            swap(ni // 2, ni)
            ni = ni // 2
    else:
        print(heap[1])
        nv = heap.pop()
        if len(heap) == 1:
            continue

        heap[1] = nv
        ni = 1
        while ni * 2 + 1 < len(heap):
            c1, c2 = heap[ni * 2], heap[ni * 2 + 1]
            if nv >= max(c1, c2):
                break
            elif c2 >= c1:
                # sinking to right subtree
                nni = ni * 2 + 1
                swap(nni, ni)
                ni = nni
            elif c1 > c2:
                # sinking to the left
                nni = ni * 2
                swap(nni, ni)
                ni = nni

        if ni * 2 < len(heap) and nv < heap[ni * 2]:
            swap(ni, ni * 2)
