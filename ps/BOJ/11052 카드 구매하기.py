
def solution(n, p):
    dp = [0]*1001
    
    for i in range(1, n+1):
        for j in range(1, i+1):
            dp[i] = max(dp[i], dp[i-j] + p[j])
    
    return dp[n]


def main():
    n = int(input())
    p = [0]
    for i in map(int, input().split()):
        p.append(i)
    
    answer = solution(n, p)
    
    print(answer)


if __name__ == "__main__":
    main()
