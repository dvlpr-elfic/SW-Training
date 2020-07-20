import java.util.*;

class Solution {
    private int[] times;

    private int getTime(int progress, int speed) {
        int remain = 100 - progress;
        if(remain % speed == 0) {
            return remain / speed;
        } else {
            return remain / speed + 1;
        }
    }

    private void setTimes(int[] progresses, int[] speeds) {
        times = new int[progresses.length];
        for(int i = 0; i < progresses.length; i++) {
            times[i] = getTime(progresses[i], speeds[i]);
        }
    }

    private int getCount(int idx, int length) {
        int cnt = 0;
        int base = times[idx];
        for(int i = idx; i < length; i++) {
            if(times[i] > base) {
                break;
            }
            cnt++;
        }
        return cnt;
    }

    private int[] toArray(List<Integer> list) {
        int[] ret = new int[list.size()];
        for (int i = 0; i < list.size(); i++) {
            ret[i] = list.get(i);
        }
        return ret;
    }

    public int[] solution(int[] progresses, int[] speeds) {
        List<Integer> answers = new ArrayList<>();
        setTimes(progresses, speeds);
        int idx = 0;
        while (idx < progresses.length) {
            int count = getCount(idx, progresses.length);
            answers.add(count);
            idx += count;
        }
        return toArray(answers);
    }
}

