/* 有进行当前弧优化的Dinic */
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int NMAX = 100024, MMAX = 1000000, INF = 0x3fffffff;
struct Edge{
    int to, cap, next;
};

char maze[17][17];
int n, m, dir[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};//{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};//dir的顺序居然会影响到是否超时
bool vis[16][16];

Edge edge[MMAX];
int head[NMAX], dist[NMAX], cur[NMAX], edgeNum;

bool checkResult(int x, int y){
    if(maze[x][y] == '@') return true;
    for(int i = 0; i < 4; ++i){
        int tx = x + dir[i][0], ty = y + dir[i][1];
        if(tx >= 0 && tx < n && ty >= 0 && ty < m && !vis[tx][ty] && maze[tx][ty] != '#'){
            vis[tx][ty] = true;
            if(checkResult(tx, ty)) return true;
            vis[tx][ty] = false;
        }
    }
    return false;
}

void init(int n){
    //memset(head, -1, sizeof(head));
    for(int i = 0; i <= n; ++i) head[i] = -1;
    edgeNum = 0;
}

void addEdge(int u, int v, int cap, int rw = 0){
    Edge E1 = {v, cap, head[u]};
    edge[edgeNum] = E1;
    head[u] = edgeNum++;
    Edge E2 = {u, rw, head[v]};
    edge[edgeNum] = E2;
    head[v] = edgeNum++;
}

bool bfs(int st, int ed){
    queue<int> que;
    memset(dist, -1, sizeof(dist));
    que.push(st); dist[st] = 0;
    while(!que.empty()){
        int u = que.front(); que.pop();
        for(int i = head[u]; i != -1; i = edge[i].next){
            Edge E = edge[i];
            if(dist[E.to] < 0 && E.cap){
                dist[E.to] = dist[u] + 1;
                if(E.to == ed) return true;
                que.push(E.to);
            }
        }
    }
    return false;
}

int dfs(int x, int a, int ed){
    if(x == ed) return a;
    int f;
    for(int &i = cur[x]; i != -1; i = edge[i].next){
        Edge &E = edge[i];
        if(dist[x] + 1 == dist[E.to] && E.cap > 0 && (f = dfs(E.to, min(a, E.cap), ed)) > 0){
            E.cap -= f;
            edge[i ^ 1].cap += f;
            return f;
        }
    }
    return 0;
}

int Dinic(int st, int ed){
    int flow = 0;
    while(bfs(st, ed)){
        //memcpy(cur, head, sizeof(head));
        for(int i = 0; i <= ed; ++i) cur[i] = head[i];
        int temp;
        while(temp = dfs(st, INF, ed)) flow += temp;
    }
    return flow;
}

void buildMap(int mid, int st, int ed){
    init(ed);
    int tp = n * m, tm = 2 * n * m;
    for(int k = 0; k < mid; ++k){
        int cnt = k * tm;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if(maze[i][j] != '#'){
                    if(k == 0 && maze[i][j] == 'X') addEdge(st, cnt + i * m + j + 1, 1);
                    addEdge(cnt + i * m + j + 1, cnt + tp + i * m + j + 1, 1);
                    if(maze[i][j] == '@'){
                        addEdge(cnt + tp + i * m + j + 1, ed, 1);
                    }else{
                        addEdge(cnt + tp + i * m + j + 1, cnt + tm + i * m + j + 1, 1);
                        if(i != 0 && maze[i - 1][j] != '#') addEdge(cnt + tp + i * m + j + 1, cnt + tm + (i - 1) * m + j + 1, 1);
                        if(i != n - 1 && maze[i + 1][j] != '#') addEdge(cnt + tp + i * m + j + 1, cnt + tm + (i + 1) * m + j + 1, 1);
                        if(j != 0 && maze[i][j - 1] != '#') addEdge(cnt + tp + i * m + j + 1, cnt + tm + i * m + j, 1);
                        if(j != m - 1 && maze[i][j + 1] != '#') addEdge(cnt + tp + i * m + j + 1, cnt + tm + i * m + j + 2, 1);
                    }
                }
            }
        }
    }
}

int main(){
    while(scanf("%d%d", &n, &m) == 2){
        for(int i = 0; i < n; ++i){
            scanf("%s", maze[i]);
        }
        bool flag = true;
        int num = 0;
        for(int i = 0; i < n && flag; ++i){
            for(int j = 0; j < m && flag; ++j){
                if(maze[i][j] == 'X'){
                    memset(vis, 0, sizeof(vis));
                    ++num;
                    if(!checkResult(i, j)) flag = false;
                }
            }
        }
        if(!flag){
            printf("-1\n");
        }else{
            int left = 0, right = n * m, ans = 0;
            while(left <= right){
                int mid = (left + right) / 2;
                int st = 0, ed = mid * 2 * n * m + n * m + 1;
                buildMap(mid, st, ed);
                if(Dinic(st, ed) < num){
                    left = mid + 1;
                }else{
                    ans = mid - 1;
                    right = mid - 1;
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}

