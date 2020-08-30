
def list_copy(src):
    ret = []
    for item in src:
        ret.append(item)
    return ret


def perm(depth, n, m, start, temp, answer):
    if depth == m:
        answer.append(list_copy(temp))
        return

    for i in range(start, n+1):
        if not picked[i]:
            picked[i] = True
            temp.append(i)
            perm(depth+1, n, m, i+1, temp, answer)
            picked[i] = False
            temp.pop()


def solve(n, m):
    answer = []
    perm(0, n, m, 1, [], answer)
    return answer


def main():
    n, m = map(int, input().split())
    global picked
    picked = [False]*(n+1)
    answer = solve(n, m)
    for arr in answer:
        for item in arr:
            print(item, end=' ')
        print()


if __name__ == "__main__":
    main()
