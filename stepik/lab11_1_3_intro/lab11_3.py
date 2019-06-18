def fib_digit(n):
    if not n:
        return 0
    elif n == 1:
        return 1
    else:
        a = 0
        b = 1
        for i in range(n - 1):
            a, b = b, (a + b) % 10
            
        return b


def main():
    n = int(input())
    print(fib_digit(n))


if __name__ == "__main__":
    main()