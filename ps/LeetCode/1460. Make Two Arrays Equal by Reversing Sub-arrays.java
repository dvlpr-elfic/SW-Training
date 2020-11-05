
class Solution {
    private int[] check;

    public boolean canBeEqual(int[] target, int[] arr) {
        check = new int[1001];
        for (int i = 0; i < arr.length; i++) {
            check[arr[i]]++;
        }
        for (int i = 0; i < target.length; i++) {
            if (check[target[i]] == 0) {
                return false;
            } else {
                check[target[i]]--;
            }
        }
        return true;
    }
}

