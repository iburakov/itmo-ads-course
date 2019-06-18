arr = list(map(int, input().split()))
n = arr.pop(0)
_, *qs = map(int, input().split())

ans = []
for qv in qs:
    l = 0
    r = len(arr) - 1
    pivot = (l + r) // 2
    while arr[pivot] != qv and l != r + 1:
        if qv > arr[pivot]:
            l = pivot + 1
        else:
            r = pivot - 1
        pivot = (l + r) // 2

    ans.append(-1 if arr[pivot] != qv else pivot + 1)

print(" ".join(map(str, ans)))