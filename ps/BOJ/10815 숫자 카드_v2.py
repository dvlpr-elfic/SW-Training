
def get_input():
    n = int(input())
    cards = {key: True for key in list(map(int, input().split()))}
    m = int(input())
    finds = list(map(int, input().split()))

    return n, m, cards, finds


def search(target, cards):
    if cards.get(target) is None:
        return 0
    else:
        return 1


def run():
    # input
    n, m, cards, finds = get_input()
    # solve
    results = [search(target, cards) for target in finds]
    # print
    for result in results:
        print("{} ".format(result), end='')


run()

 