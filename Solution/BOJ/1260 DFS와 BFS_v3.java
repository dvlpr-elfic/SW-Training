
import java.util.*;

class Run {
    private int n;
    private int start;
    private boolean[][] graph = new boolean[1001][1001];
    private boolean[] visited;
    private Queue<Integer> q = new LinkedList<Integer>();
    private List<Integer> dfsPath = new ArrayList<Integer>();
    private List<Integer> bfsPath = new ArrayList<Integer>();

    public void input() {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        int m = sc.nextInt();
        start = sc.nextInt();
        for( ; m > 0; m--) {
            int i, j;
            i = sc.nextInt();
            j = sc.nextInt();
            graph[i][j] = true;
            graph[j][i] = true;
        }
    }

    private void dfs(int cur) {
        visited[cur] = true;
        dfsPath.add(cur);
        for(int i = 1; i <= n; i++) {
            if(graph[cur][i] && !visited[i]) {
                dfs(i);
            }
        }
    }

    private void bfs(int start) {
        q.add(start);
        visited[start] = true;
        while(!q.isEmpty()) {
            int cur = q.poll().intValue();
            bfsPath.add(cur);
            for(int next = 1; next <= n; next++) {
                if(!graph[cur][next])    continue;
                if(visited[next])    continue;
                visited[next] = true;
                q.add(next);
            }
        }
    }

    public void solve() {
        visited = new boolean[1001];
        bfs(start);
        visited = new boolean[1001];
        dfs(start);
    }

    public void print() {
        for (Integer v : dfsPath) {
            System.out.print(v + " ");
        }
        System.out.println("");
        for (Integer v : bfsPath) {
            System.out.print(v + " ");
        }
        System.out.println("");
    }
}

class Main {
    public static void main(String[] args) {
        Run run = new Run();
        run.input();
        run.solve();
        run.print();
    }
}

  