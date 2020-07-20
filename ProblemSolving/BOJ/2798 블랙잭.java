import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

class Run {
    private int target;
    private int[] cards;
    private int result;
    private int[] pickedCards;

    public void input() {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        target = sc.nextInt();
        cards = new int[n];
        for (int i = 0; i < n; i++) {
            cards[i] = sc.nextInt();
        }
        pickedCards = new int[n];
        result = 0;
    }

    private int getSumOfPickedCards() {
        int ret = 0;
        for (int pickedCard : pickedCards) {
            ret += pickedCard;
        }
        return ret;
    }

    private int pickCards(int start, int depth) {
        if (depth == 3) {
            return getSumOfPickedCards();
        }

        int ret = Integer.MIN_VALUE;

        for (int i = start; i < cards.length; i++) {
            pickedCards[depth] = cards[i];
            int temp = pickCards(i + 1, depth + 1);
            if (temp <= target) {
                ret = Math.max(ret, temp);
            }
        }
        return ret;
    }

    public void solve() {
        result = pickCards(0, 0);
    }

    public void print() {
        System.out.println(result);
    }
}

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
//        System.setIn(new FileInputStream("res/input.txt"));
        Run run = new Run();
        run.input();
        run.solve();
        run.print();
    }
}

