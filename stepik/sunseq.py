n = int(input())
d = [1]*n
a = list(map(int, input().split()))
for i in range(1, n):
    acceptable = []
    for j in range(i):
        if a[i] % a[j] == 0 and d[j] + 1 > d[i]:
            acceptable.append(d[j])

    d[i] = 1 + max(acceptable or [0])
print(max(d))