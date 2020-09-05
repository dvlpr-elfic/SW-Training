
def solve(depth, n, m, start, temp, answers, numbers):
    if depth == m:
        new_arr = [_ for _ in temp]
        answers.append(new_arr)
        return None
    
    for i in range(start, n):
        temp.append(numbers[i])
        solve(depth+1, n, m, i+1, temp, answers, numbers)
        temp.pop()
    
    return None


def main():
    # input
    n, m = map(int, input().split())
    numbers = list(map(int, input().split()))
    # solve
    numbers.sort()
    answers = []
    solve(0, n, m, 0, [], answers, numbers)
    # print
    for answer in answers:
        for number in answer:
            print(number, end=' ')
        print()


if __name__ == "__main__":
    main()
