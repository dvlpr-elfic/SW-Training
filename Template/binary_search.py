
def find(arr, target):
    left = 0
    right = len(arr) - 1
    while left <= right:
        mid = int((left + right) / 2)
        if arr[mid] == target:
            return mid
        elif arr[mid] > target:
            right = mid - 1
        else:
            left = mid + 1
    return "not found"


def main():
    arr = [1, 3, 4, 5, 9, 10, 21, 33, 45, 100]
    print("find {} : {}".format(11, find(arr, 11)))
    print("find {} : {}".format(5, find(arr, 5)))
    return 0
    

if __name__ == "__main__":
    exit(main())

