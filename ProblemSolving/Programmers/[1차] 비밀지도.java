class Solution {
    
    private void sout(Object o) {
        System.out.println(o);
    }
    
    private String[] charArrToStringArr(char[][] src) {
        String[] ret = new String[src.length];
        
        for (int i = 0; i < src.length; i++) {
            ret[i] = String.valueOf(src[i]);
        }
        
        return ret;
    }
    
    private char[] getCode(int code, int n) {
        char[] ret = new char[n];
        int size = 0;
        
        for (int base = 1 << (n - 1); base > 0; base = base >> 1) {
            // sout("base : " + base);
            // sout("code : " + code);
            if ((code & base) == 0) {
                ret[size++] = ' ';
            } else {
                ret[size++] = '#';
            }
        }
        
        return ret;
    }
    
    private void orString(char[] dst, char[] src) {
        for (int i = 0; i < src.length; i++) {
            if (dst[i] == '#') {
                continue;
            } else if(src[i] == '#') {
                dst[i] = '#';
            } else {
                dst[i] = ' ';
            }
        }
    }
    
    public String[] solution(int n, int[] arr1, int[] arr2) {
        String[] answer;
        char[][] map = new char[n][n];
        
        for (int i = 0; i < arr1.length; i++) {
            char[] code = getCode(arr1[i], n);
            orString(map[i], code);
            code = getCode(arr2[i], n);
            orString(map[i], code);
        }
        
        return charArrToStringArr(map);
    }
}

