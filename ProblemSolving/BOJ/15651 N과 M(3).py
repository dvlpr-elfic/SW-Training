
def solve(depth, n, m, answer, tmp):
    if depth == m:
        new_arr = [_ for _ in tmp]
        answer.append(new_arr)
        return None
    
    for cur in range(1, n+1):
        tmp.append(cur)
        solve(depth+1, n, m, answer, tmp)
        tmp.pop()


def main():
    # input
    n, m = map(int, input().split())
    answer = []
    # solve
    solve(0, n, m, answer, [])
    # print
    for arr in answer:
        for item in arr:
            print("{} ".format(item), end='')
        print()


if __name__ == "__main__":
    main()
