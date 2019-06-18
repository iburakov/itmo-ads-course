n, tw = map(int, input().split())


class Product:
    def __init__(self, cost, weight):
        self.cost = cost
        self.weight = weight

    @property
    def wcost(self):
        return self.cost / self.weight


goods = sorted(map(lambda s: Product(*map(int, s.split())), (input() for i in range(n))),
               key=lambda p: p.wcost)

tc = 0
while tw and goods:
    nxt = goods.pop()
    taken = min(tw, nxt.weight)
    tc += taken * nxt.wcost
    tw -= taken

print(tc)
