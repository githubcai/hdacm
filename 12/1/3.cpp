#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 16;

struct Edge{
    int v, next;
};

struct Node{
    int s, d;
};

int n, m, id[MAX][MAX], c[MAX][2], ids, fin;
char maze[MAX][MAX];
Edge edge[MAX * MAX * 4];
int cnt, head[MAX * MAX], dist[MAX][MAX];
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
bool vis[MAX * MAX];
int dp[1 << MAX][MAX];

void init(){
    memset(id, -1, sizeof(id));
    memset(head, -1, sizeof(head));
    memset(dist, -1, sizeof(dist));
    cnt = 0, ids = 1, fin = 0;
}

void addEdge(int u, int v){
    edge[cnt].v = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void bfs(int s){
    queue<Node> que;
    Node now, next;
    memset(vis, 0, sizeof(vis));
    now.s = s, now.d = 0;
    vis[s] = true;
    que.push(now);
    while(!que.empty()){
        now = que.front();
        que.pop();
        int u = now.s;
        if(id[u / m][u % m] != -1) dist[id[s / m][s % m]][id[u / m][u % m]] = now.d;
        for(int i = head[u]; i != -1; i = edge[i].next){
            int v = edge[i].v;
            if(vis[v]) continue;
            vis[v] = true;
            next.s = v, next.d = now.d + 1;
            que.push(next);
        }
    }
}

bool solve(int mid){
    memset(dp, -1, sizeof(dp));
    dp[1][0] = mid;
    for(int i = 1; i < (1 << ids); ++i){
        for(int j = 0; j < ids; ++j){
            if((i & (1 << j)) == 0 || dp[i][j] == -1) continue;
            if((i & fin) == fin) return true;
            for(int k = 0; k < ids; ++k){
                if((i & (1 << k)) || dist[j][k] == -1) continue;
                if(dp[i][j] >= dist[j][k]){
                    if(dp[i | (1 << k)][k] == -1 || dp[i | (1 << k)][k] < dp[i][j] - dist[j][k]){
                        dp[i | (1 << k)][k] = dp[i][j] - dist[j][k];
                    }
                    if(maze[c[k][0]][c[k][1]] == 'G') dp[i | (1 << k)][k] = mid;
                }
            }
        }
    }
    return false;
}

int main(){
    while(scanf("%d%d", &n, &m) != EOF && n != 0 && m != 0){
        init();
        for(int i = 0; i < n; ++i){
            scanf("%s", maze[i]);
        }
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if(maze[i][j] == 'D') continue;
                if(maze[i][j] == 'F'){
                    c[0][0] = i, c[0][1] = j;
                    id[i][j] = 0;
                }else if(maze[i][j] == 'G'){
                    c[ids][0] = i, c[ids][1] = j;
                    id[i][j] = ids++;
                }else if(maze[i][j] == 'Y'){
                    c[ids][0] = i, c[ids][1] = j;
                    id[i][j] = ids++;
                    fin |= (1 << (ids - 1));
                }
                for(int k = 0; k < 4; ++k){
                    int x = i + dir[k][0], y = j + dir[k][1];
                    if(x >= 0 && x < n && y >= 0 && y < m && maze[x][y] != 'D'){
                        addEdge(i * m + j, x * m + y);
                    }
                }
            }
        }
        for(int i = 0; i < ids; ++i){
            bfs(c[i][0] * m + c[i][1]);
        }
        int left = 0, right = n * m * (ids - 1), ans = -1;
        while(left <= right){
            int mid = (left + right) >> 1;
            if(solve(mid)){
                ans = mid;
                right = mid - 1;
            }else{
                left = mid + 1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
