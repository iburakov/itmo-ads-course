def fib_mod(n, m):
    if not n:
        return 0
    elif n <= 2:
        return 1
    else:
        saved = [0, 1]
        for i in range(n - 1):
            saved.append((saved[-1] + saved[-2]) % m)
            if saved[-1] == 1 and saved[-2] == 0:
                m = len(saved) - 2
                break
               
        return saved[n % m]


def main():
    n, m = map(int, input().split())
    print(fib_mod(n, m))


if __name__ == "__main__":
    main()