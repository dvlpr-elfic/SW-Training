
def solve(n):
    dp = [0]*(n+1)
    
    for i in range(1, n+1):
        if i == 1 or i == 2:
            dp[i] = 1 if i == 1 else 3
        else:
            dp[i] = dp[i-1] + dp[i-2] + dp[i-2]
    
    return dp[n]%10007


def main():
    n = int(input())
    answer = solve(n)
    print(answer)


if __name__ == "__main__":
    main()
