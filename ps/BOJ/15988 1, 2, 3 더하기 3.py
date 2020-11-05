
MOD = 1000000009
MAX = 1000001

def solve(n, dp):
    for x in range(1, n+1):
        if x == 1 or x == 2 or x == 3:
            dp[x] = 1<<(x-1)
        else:
            dp[x] = (dp[x-1] + dp[x-2] + dp[x-3])%MOD

    return dp[n]


def main():
    # input
    answers = []
    t = int(input())
    dp = [0]*MAX
    for _ in range(t):
        n = int(input())
        # solve
        answers.append(solve(n, dp))
    
    # print
    for answer in answers:
        print(answer)

if __name__ == "__main__":
    main()
