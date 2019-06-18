n, m = map(int, input().split())
rcode = {}
for i in range(n):
    c, seq = input().split(": ")
    rcode[seq] = c

encoded = input()
decoded = []
cc = ""
for i in range(m):
    if cc in rcode:
        decoded.append(rcode[cc])
        cc = encoded[i]
    else:
        cc += encoded[i]
decoded.append(rcode[cc])

print("".join(decoded))
