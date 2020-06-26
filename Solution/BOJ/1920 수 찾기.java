import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

class Solution {

    private final static int MAX = 100001;
    private int n;
    private int m;

    private int[] a;
    private int[] x;
    private int[] result;

    private void sort(int[] arr, int left, int right) {
        if (left >= right) return;
        int l = left - 1;
        int r = right + 1;
        int mid = arr[(l + r) / 2];
        while (true) {
            while (compare(arr[++l], mid)) ;
            while (compare(mid, arr[--r])) ;
            if (l >= r) break;
            int temp = arr[l];
            arr[l] = arr[r];
            arr[r] = temp;
        }
        sort(arr, left, l - 1);
        sort(arr, r + 1, right);
    }

    private boolean compare(int n1, int n2) {
        return n1 < n2;
    }


    public void input() {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = sc.nextInt();
        }
        m = sc.nextInt();
        x = new int[m];
        for (int i = 0; i < m; i++) {
            x[i] = sc.nextInt();
        }
    }

    public void solve() {
        sort(a, 0, n - 1);
        result = new int[m];
        for (int i = 0; i < m; i++) {
            result[i] = binarySearch(a, x[i]);
        }
    }

    private int binarySearch(int[] arr, int target) {
        int left = 0;
        int right = arr.length - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (arr[mid] > target) {
                right = mid - 1;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                return 1;
            }
        }
        return 0;
    }

    public void print() {
        for (int i = 0; i < result.length; i++) {
            System.out.println(result[i]);
        }
    }
}

class Main {
    public static void main(String[] args) throws FileNotFoundException {
//        System.setIn(new FileInputStream("res/input.txt"));
        Solution solution = new Solution();
        solution.input();
        solution.solve();
        solution.print();
    }
}
