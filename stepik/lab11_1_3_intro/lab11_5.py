def gcd(a, b):
    if not a or not b:
        return a or b
    
    if b > a:
        a, b = b, a
    
    return gcd(a % b, b)


def main():
    a, b = map(int, input().split())
    print(gcd(a, b))


if __name__ == "__main__":
    main()