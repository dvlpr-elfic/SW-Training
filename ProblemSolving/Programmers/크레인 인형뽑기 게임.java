import java.util.Stack;

class Run {
    private final Stack<Integer> stack;

    public Run() {
        stack = new Stack<>();
    }

    private int getTopY(int[][] map, int x) {
        for (int y = 0; y < map.length; y++) {
            if (map[y][x] != 0) {
                return y;
            }
        }
        return -1;
    }

    private int remove(int[][] map, int x, int y) {
        int ret = map[y][x];
        map[y][x] = 0;
        return ret;
    }

    public int move(int[][] map, int x) {
        int y = getTopY(map, x);
        if (y < 0) {
            return 0;
        }
        int item = remove(map, x, y);
        if (!stack.empty() && stack.peek().equals(item)) {
            stack.pop();
            return 2;
        } else {
            stack.push(item);
            return 0;
        }
    }
}

class Solution {

    public int solution(int[][] board, int[] moves) {
        int ret = 0;
        Run run = new Run();
        for (int move : moves) {
            ret += run.move(board, move - 1);
        }
        return ret;
    }
}

