import java.util.*;

class Solution {
    
    private void sout(Object o) {
        System.out.println(o);
    }
    
    public String solution(String[] participant, String[] completion) {
        String answer = "";
        HashMap<String, Integer> map = new HashMap<>();
        for (String player : participant) {
            Integer count = map.get(player);
            if (count == null) {
                map.put(player, 1);
            } else {
                map.put(player, count + 1);
            }
        }
        
        for (String player : completion) {
            Integer count = map.get(player);
            map.put(player, count - 1);
        }
        
        Iterator it = map.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry entry = (Map.Entry) it.next();
            if ((Integer)entry.getValue() > 0) {
                answer = (String)entry.getKey();
                break;
            }
        }
        
        return answer;
    }
}

