import static java.util.Arrays.sort;

class Solution {
    private int i;
    private int j;
    private int k;
    private int[] temp;

    private void setIJK(int[] command) {
        i = command[0] - 1;
        j = command[1] - 1;
        k = command[2] - 1;
    }

    private void setTempArray(int[] array) {
        temp = new int[j - i + 1];
        int cnt = 0;
        for (int idx = i; idx <= j; idx++) {
            temp[cnt++] = array[idx];
        }
    }

    public int[] solution(int[] array, int[][] commands) {
        int[] answer = new int[commands.length];
        for (int tc = 0; tc < commands.length; tc++) {
            setIJK(commands[tc]);
            setTempArray(array);
            sort(temp);
            answer[tc] = temp[k];
        }
        return answer;
    }
}
