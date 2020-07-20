
class Solution {
    private int answer = 0;
    private int n;
    private boolean[] picked;
    private String[] arr;
    private boolean[] check = new boolean[9999999];
    
    private int isPrime(String str) {
        int target = Integer.parseInt(str);
        if (check[target]) {
            return 0;
        }
        else {
            check[target] = true;
        }
        if (target == 1 || target == 0) {
            return 0;
        }
        else if (target == 2) {
            return 1;
        }
        for (int i=2; i<target; i++) {
            if(target%i == 0) {
                return 0;
            }
        }
        return 1;
    }
    
    private void print(Object o) {
        System.out.println(o);
    }
    
    private int recur(int depth, String cur, int limit) {
        if (depth == limit) {
            return isPrime(cur);
        }
        int ret = 0;
        for (int i=0; i<picked.length; i++) {
            if (!picked[i]) {
                picked[i] = true;
                ret += recur(depth+1, cur+arr[i], limit);
                picked[i] = false;
            }
        }
        return ret;
    }
    
    public int solution(String numbers) {
        arr = numbers.split("");
        n = arr.length;
        picked = new boolean[arr.length];
        for (int i=1; i<=n; i++) {
            answer += recur(0, "", i);
        }
        return answer;
    }
}
 