
MOD = 1000000000

def solution(n):
    ret = 0
    dp = [[1]*10 for _ in range(n+1)]

    for h in range(2, n+1):
        for x in range(10):
            if x == 0:
                dp[h][0] = dp[h-1][1]
            elif x == 9:
                dp[h][9] = dp[h-1][8]
            else:
                dp[h][x] = dp[h-1][x-1] + dp[h-1][x+1]
    
    for x in range(1, 10):
        ret += dp[n][x]
    
    return ret % MOD


def main():
    # input
    n = int(input())
    # solve
    answer = solution(n)
    # print
    print(answer)


if __name__ == "__main__":
    main()
