import java.util.Scanner;

class Solver {
    private int n;
    private int m;
    private int[] array;
    private int result;
    private int maxHeight = Integer.MIN_VALUE;

    public void input() {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        m = sc.nextInt();
        array = new int[n];
        for (int i = 0; i < n; i++) {
            array[i] = sc.nextInt();
            maxHeight = Math.max(maxHeight, array[i]);
        }
    }

    private long cut(int height) {
        long ret = 0;
        for (int i = 0; i < n; i++) {
            if (array[i] > height) {
                ret += array[i] - height;
            }
        }
        return ret;
    }

    private int binarySearch() {
        int ret = Integer.MIN_VALUE;
        int left = 0;
        int right = maxHeight;
        while (left <= right) {
            int mid = (left + right) / 2;
            long res = cut(mid);
            if (res >= m) {
                ret = Math.max(ret, mid);
            }
            if (res < m) {
                // 더 짧게 잘라야함
                right = mid - 1;
            } else if (res > m) {
                // 더 길게 잘라야함
                left = mid + 1;
            } else {
                // 최적
                break;
            }
        }
        return ret;
    }

    public void solve() {
        result = binarySearch();
    }

    public void print() {
        System.out.println(result);
    }
}

public class Main {
    public static void main(String[] args) {
//        System.setIn(new FileInputStream("res/input.txt"));
        Solver solver = new Solver();
        solver.input();
        solver.solve();
        solver.print();
    }
}

