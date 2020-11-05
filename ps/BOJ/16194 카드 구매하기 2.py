
def solution(n, p):
    dp = [987654321]*(n+1)
    dp[0] = 0
    for i in range(1, n+1):
        for j in range(1, i+1):
            dp[i] = min(dp[i], dp[i-j] + p[j])
            
    return dp[n]


def main():
    # input
    n = int(input())
    p = [0]
    for item in list(map(int, input().split())):
        p.append(item)
    # solve
    answer = solution(n, p)
    # print
    print(answer)    


if __name__ == "__main__":
    main()
