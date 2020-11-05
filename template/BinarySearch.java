
public class BinarySearch {

    public static int binarySearch(int[] array, int target) {
        int left = 0;
        int right = array.length - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (array[mid] == target) {
                return mid;
            } else if (array[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return -1;

    }
    public static void main(String[] args) {
        int[] arr = {1, 3, 4, 5, 9, 10, 21, 33, 45, 100};       // 오름차순 정렬되어있는 상태
        System.out.println(BinarySearch.binarySearch(arr, 11));
        System.out.println(BinarySearch.binarySearch(arr, 5));
        // 존재하면 해당 인덱스 출력, 존재하지 않으면 -1 출력
    }
}
