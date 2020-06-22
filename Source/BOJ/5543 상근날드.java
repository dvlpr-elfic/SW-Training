import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

import static java.lang.Math.min;

class Solution {
    private int[] price;
    private int result;
    final static int INF = 987654321;

    public Solution() {
        this.price = new int[5];
        this.result = 0;
    }

    private int getMin(int[] arr, int start, int end) {
        int ret = INF;
        for (int i = start; i <= end; i++) {
            ret = min(arr[i], ret);
        }
        return ret;
    }

    public void input() throws FileNotFoundException {
        File file = new File("res\\input.txt");
        Scanner scanner = new Scanner(file);
//        Scanner scanner = new Scanner(System.in);
        for (int i = 0; i < 5; i++) {
            price[i] = scanner.nextInt();
        }
    }

    public void solve() {
        result += getMin(price, 0, 2);
        result += getMin(price, 3, 4);
        result -= 50;
    }

    public void print() {
        System.out.println(result);
    }
}

public class Main {

    public static void main(String[] args) throws FileNotFoundException {
        Solution solution = new Solution();
        solution.input();
        solution.solve();
        solution.print();
    }
}