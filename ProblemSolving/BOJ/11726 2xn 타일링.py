
def dp(n):
    if n == 1 or n == 2:
        return n
    for cur in range(3, n+1):
        memo[cur] = (memo[cur-1] + memo[cur-2])%10007
    return memo[n]

def main():
    n = int(input())
    global memo
    memo = [0]*(n+1)
    memo[1] = 1
    memo[2] = 2
    return dp(n)

if __name__ == "__main__":
    print(main())
