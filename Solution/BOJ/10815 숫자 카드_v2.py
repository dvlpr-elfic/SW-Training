
def get_input():
    n = int(input())
    cards = {key: True for key in list(map(int, input().split()))}
    m = int(input())
    finds = list(map(int, input().split()))

    return n, m, cards, finds


def search(target, cards):
    if cards.get(target) is None:
        return False
    else:
        return True


def run():
    # input
    n, m, cards, finds = get_input()
    results = []
    # solve
    for target in finds:
        if search(target, cards):
            results.append(1)
        else:
            results.append(0)
    # print
    for result in results:
        print("{} ".format(result), end='')


run()

  