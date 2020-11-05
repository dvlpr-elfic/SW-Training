
def solve(depth, n, m, start, answer, temp):
    if depth == m:
      new_arr = [_ for _ in temp]
      answer.append(new_arr)
      return None

    for cur in range(start, n+1):
      temp.append(cur)
      solve(depth+1, n, m, cur, answer, temp)
      temp.pop()

    return None


def main():
    # input
    n, m = map(int, input().split())
    # solve
    answer = []
    solve(0, n, m, 1, answer, [])
    # print
    for arr in answer:
        for number in arr:
            print(number, end=' ')
        print()

    return None


if __name__ == "__main__":
    main()
