n = int(input())
a = list(map(int, input().split()))

# minimal last elements of LIS of length i
t = [-1] * n
t[0] = 0

# where we came from when were setting t[i]
r = [-1] * n
ml = 0


def find_ceiling_in_t(x):
    l = 0  # left
    r = ml  # right
    while l <= r:
        # pivot, middle val
        p = (l + r) // 2
        if p < ml and a[t[p]] >= x >= a[t[p + 1]]:
            while a[t[p + 1]] == x:
                p += 1
            return p + 1
        elif x <= a[t[p]]:
            l = p + 1
        else:
            r = p - 1

    raise RuntimeError(" ".join(map(str, a)))


for i in range(1, n):
    if a[i] > a[t[0]]:
        # a[i] is min last elem of LIS of len 1 (stored at t[0])
        t[0] = i
        # leaving -1 in r as this should be the end of a sequence
    elif a[i] <= a[t[ml]]:
        # a[i] is not less than min last elem of curring-edge LIS
        # append it as a LIS of length (ml+1) to T
        ml += 1
        t[ml] = i
        # save where we came from
        r[i] = t[ml - 1]
    else:
        # binary search to find a ceiling of a[i] to put it there
        ci = find_ceiling_in_t(a[i])
        # update t, save new minimum
        t[ci] = i
        # save where we came from
        r[t[ci]] = t[ci - 1]

print(ml + 1)

# reassemble sequence on our way backwards
# seq = []
seqi = []
ci = t[ml]
while ci != -1:
    # seq.append(a[ci])
    seqi.append(ci + 1)
    ci = r[ci]

print(" ".join(map(str, reversed(seqi))))
