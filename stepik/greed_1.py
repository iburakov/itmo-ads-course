from operator import itemgetter

n = int(input())
areas = sorted(map(lambda s: list(map(int, s.split(" "))), (input() for i in range(n))), key=itemgetter(1))
dots = []
for s, e in areas:
    if not dots or s > dots[-1]:
        dots.append(e)

print(len(dots))
print(" ".join(map(str, dots)))