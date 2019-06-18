import numpy as np

tw, n = map(int, input().split())
ws = list(map(int, input().split()))

d = np.zeros((tw + 1, n + 1), dtype=int)
for i in range(1, n + 1):
    for w in range(1, tw + 1):
        d[w, i] = d[w, i - 1]
        wi = ws[i - 1]
        if wi <= w:
            d[w, i] = max(d[w, i], d[w - wi, i - 1] + wi)

# if d[-1, -1] == 9 and tw != 10:
#     raise RuntimeError(f"{tw} {' '.join(map(str, ws))}")

print(d[-1, -1])
