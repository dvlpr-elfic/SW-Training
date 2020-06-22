import java.util.Scanner;

class Solution {
    private int plus;
    private int minus;
    private int target;
    private int result;

    public void input() {
        Scanner scanner = new Scanner(System.in);
        this.plus = scanner.nextInt();
        this.minus = scanner.nextInt();
        this.target = scanner.nextInt();
        this.result = 0;
    }

    public void print() {
        System.out.println(this.result);
    }

    public void solve() {
        int part = this.plus - this.minus;
        this.target -= this.plus;
        if (target % part == 0) {
            result = target / part + 1;
        } else {
            result = target / part + 2;
        }
    }
}

public class Main {

    public static void main(String[] args) {
        Solution solution = new Solution();
        solution.input();
        solution.solve();
        solution.print();
    }
}