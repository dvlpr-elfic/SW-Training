
def solve(n):
    dp = [[0]*10 for _ in range(1001)]
    for i in range(10):
        dp[1][i] = 1
    for i in range(2, n+1):
        for j in range(10):
            dp[i][j] = sum(dp[i-1][j:])
    
    return sum(dp[n])%10007


def main():
    # input
    n = int(input())
    # solution
    answer = solve(n)
    # print
    print(answer)


if __name__ == "__main__":
    main()
