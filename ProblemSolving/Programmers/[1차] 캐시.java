import java.util.ArrayList;
import java.util.List;

class Cache {
    private int size;
    List<String> list;

    public Cache(int size) {
        this.size = size;
        this.list = new ArrayList<>();
    }

    private int find(String item) {
        for(int i=0; i<list.size(); i++){
            if(list.get(i).equals(item)) {
                return i;
            }
        }
        return -1;
    }

    private boolean full() {
        return this.size <= list.size();
    }

    public int push(String item) {
        if(this.size == 0) {
            return 5;
        }
        int idx = find(item);
        if(idx < 0) {
            // 못찾음, miss
            if(!full()) {
                // 캐시가 아직 자리가 있음
                list.add(item);
            } else {
                // 캐시에 자리가 없음
                list.remove(0);
                list.add(item);
            }
            return 5;
        } else {
            // 찾음, hit
            list.add(item);
            list.remove(idx);
            return 1;
        }
    }
}

class Solution {
    public int solution(int cacheSize, String[] cities) {
        int answer = 0;
        Cache cache = new Cache(cacheSize);
        for (String city : cities) {
            answer += cache.push(city.toLowerCase());
        }
        return answer;
    }
}
