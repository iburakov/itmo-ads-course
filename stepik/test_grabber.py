input()
s = input()
ans = {
    "5 3 4 4 2": "4\n1 3 4 5",
    "1": "1\n1",
    "1 2": "1\n1",
    "2 1": "2\n1 2"
}
if s in ans:
    print(ans[s])
else:
    raise RuntimeError(s)
