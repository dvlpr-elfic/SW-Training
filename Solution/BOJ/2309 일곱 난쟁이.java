import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

import static java.util.Arrays.sort;

class Solution {
    private final int[] answers = new int[7];
    private final int[] temp = new int[7];
    private final int[] heights = new int[9];

    public void input() {
        Scanner sc = new Scanner(System.in);
        for (int i = 0; i < heights.length; i++) {
            heights[i] = sc.nextInt();
        }
    }

    private int getSum(int[] numbers) {
        int ret = 0;
        for (int number : numbers) {
            ret += number;
        }
        return ret;
    }

    private void copyArray(int[] src, int[] dst) {
        for (int i = 0; i < src.length; i++) {
            dst[i] = src[i];
        }
    }

    private void picking(int depth, int start) {

        if (depth == 7) {
            if (getSum(temp) == 100) {
                copyArray(temp, answers);
            }
            return;
        }
        for (int cur = start; cur < 9; cur++) {
            temp[depth] = heights[cur];
            picking(depth + 1, cur + 1);
        }
    }

    public void solve() {
        picking(0, 0);
    }

    public void print() {
        sort(answers);
        for (int answer : answers) {
            System.out.println(answer);
        }
    }
}

class Main {
    public static void main(String[] args) throws FileNotFoundException {
//        System.setIn(new FileInputStream("res/input.txt"));
        Solution s = new Solution();
        s.input();
        s.solve();
        s.print();
    }
}

