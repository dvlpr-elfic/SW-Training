
def init_dp():
    dp = [[0]*4 for _ in range(100001)]
    
    dp[1][1] = 1
    dp[1][2] = 0
    dp[1][3] = 0

    dp[2][1] = 0
    dp[2][2] = 1
    dp[2][3] = 0

    dp[3][1] = dp[3][2] = dp[3][3] = 1

    return dp


def solution(n, dp):

    if dp[n][1] != 0:
        return sum(dp[n])%1000000009
    
    for i in range(4, n+1):
        dp[i][1] = (dp[i-1][2] + dp[i-1][3])%1000000009
        dp[i][2] = (dp[i-2][1] + dp[i-2][3])%1000000009
        dp[i][3] = (dp[i-3][1] + dp[i-3][2])%1000000009
    
    return sum(dp[n])%1000000009

def main():
    dp = init_dp()
    # input
    t = int(input())
    answers = list()
    for tc in range(t):
        n = int(input())
        answers.append(solution(n, dp))

    for answer in answers:
        print(answer)

if __name__ == "__main__":
    main()
