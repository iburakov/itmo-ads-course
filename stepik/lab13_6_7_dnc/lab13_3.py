from collections import Counter

n = int(input())
print("".join(f" {c}" * num for c, num in sorted(Counter(map(int, input().split())).items())).strip())

