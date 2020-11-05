import java.util.*;

class Solution {
    private int x;
    private int y;
    private int res;

    private int getQuadrant() {
        if (x > 0 && y > 0) {
            return 1;
        } else if (x > 0 && y < 0) {
            return 4;
        } else if (x < 0 && y < 0) {
            return 3;
        } else if (x < 0 && y > 0) {
            return 2;
        } else
            return 0;
    }

    public void input() throws Exception {
        Scanner scanner = new Scanner(System.in);
        this.x = scanner.nextInt();
        this.y = scanner.nextInt();
    }

    public void solve() {
        this.res = getQuadrant();
    }

    public void print() {
        System.out.println(this.res);
    }
}

class Main {
    public static void main(String[] args) throws Exception {
        Solution sol = new Solution();
        sol.input();
        sol.solve();
        sol.print();
    }
}