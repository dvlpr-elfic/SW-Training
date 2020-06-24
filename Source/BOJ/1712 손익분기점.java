import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

class Solution {
    private int fix;                // 제품 출시 비용(?)(고정비용)
    private int produce;            // 제품 생산 비용
    private int price;              // 제품 가격
    private int result;

    public void input() {
        Scanner sc = new Scanner(System.in);
        this.fix = sc.nextInt();
        this.produce = sc.nextInt();
        this.price = sc.nextInt();
    }

    public void solve() {
        if (this.produce >= this.price) {
            this.result = -1;
        } else {
            this.result = this.fix / (this.price - this.produce) + 1;
        }
    }

    public void print() {
        System.out.println(result);
    }
}

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
//        System.setIn(new FileInputStream("res/input.txt"));
        Solution solution = new Solution();
        solution.input();
        solution.solve();
        solution.print();
    }
}