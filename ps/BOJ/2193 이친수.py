
def solve(n):
    dp = [[0, 1] for _ in range(91)]

    for i in range(2, n+1):
        dp[i][1] = dp[i-1][0]
        dp[i][0] = dp[i-1][0] + dp[i-1][1]

    return sum(dp[n])


def main():
    # input
    n = int(input())
    # solution
    answer = solve(n)
    # print
    print(answer)


if __name__ == "__main__":
    main()
