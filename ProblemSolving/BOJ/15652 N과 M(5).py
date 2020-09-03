
def solve(depth, n, m, temp, arr):
    if depth == m:
        new_arr = [_ for _ in temp]
        answer.append(new_arr)
        return None

    for i in range(n):
        if not picked[i]:
            temp.append(arr[i])
            picked[i] = True
            solve(depth+1, n, m, temp, arr)
            temp.pop()
            picked[i] = False


def main():
    # input
    n, m = map(int, input().split())
    global picked
    picked = [False]*n
    arr = list(map(int, input().split()))
    # sort
    arr.sort()
    # solve
    global answer
    answer = []
    solve(0, n, m, [], arr)
    # print
    for line in answer:
        for number in line:
            print(number, end=' ')
        print()


if __name__ == "__main__":
    main()
