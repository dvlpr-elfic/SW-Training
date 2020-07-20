import java.util.*;

class Solution {
    private void sout(Object o) {
        System.out.println(o);
    }
    
    private String getStrCode(int code, int n) {
        String ret = "";
        for (int base = 1 << (n - 1); base > 0; base = base >> 1) {
            if ((code & base) == 0) {
                ret += " ";
            } else {
                ret += "#";
            }
        }
        return ret;
    }
    
    public String[] solution(int n, int[] arr1, int[] arr2) {
        String[] answer = new String[n];
        for (int i = 0; i < n; i++) {
            int code = arr1[i] | arr2[i];
            sout("code : " + code);
            answer[i] = getStrCode(code, n);
        }
        return answer;
    }
}
