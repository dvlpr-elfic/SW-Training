
def solve(a, n):
    if n <= 3:
        return a[n]
    else:
        for x in range(4, n+1):
            a[x] = a[x-1] + a[x-2] + a[x-3]
        return a[n]

def main():
    a = [0]*12
    a[1] = 1
    a[2] = 2
    a[3] = 4
    t = int(input())
    for _ in range(t):
        n = int(input())
        print(solve(a, n))
    return None


if __name__ == "__main__":
    main()
