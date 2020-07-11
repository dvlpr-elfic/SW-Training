
def get_input():
    n = int(input())
    cards = list(map(int, input().split()))
    m = int(input())
    finds = list(map(int, input().split()))

    return n, m, cards, finds

def search(target, cards):
    right = len(cards) - 1
    left = 0
    while left <= right:
        mid = int((left + right) / 2)
        if cards[mid] < target:
            left = mid + 1
        elif cards[mid] > target:
            right = mid - 1
        else:
            return True
    return False

def run():
    # input
    n, m, cards, finds = get_input()
    cards.sort()
    results = []
    # solve
    for target in finds:
        if search(target, cards):
            results.append(1)
        else:
            results.append(0)
    # print
    for result in results:
        print("{} ".format(result), end = '')

run()

 