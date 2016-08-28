#include <cstdio>
#include <cstring>

const int MAX = 101, INF = 0x7fffff;
int verNum, maze[MAX][MAX], dist[MAX];
bool used[MAX];

void Dijkstra(int v){
    memset(used, 0, sizeof(used));
    for(int i = 0; i < verNum; ++i){
        dist[i] = maze[v][i];
    }
    used[v] = true;
    for(int i = 1; i < verNum; ++i){
        int tMin = INF, mark;
        for(int j = 0; j < verNum; ++j){
            if(!used[j] && dist[j] < tMin){
                tMin = dist[j];
                mark = j;
            }
        }
        used[mark] = true;
        for(int j = 0; j < verNum; ++j){
            if(!used[j] && dist[j] > dist[mark] + maze[mark][j]){
                dist[j] = dist[mark] + maze[mark][j];
            }
        }
    }
}

int max(int a, int b){
    return a > b ? a : b;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T-- > 0){
        int n, m;
        scanf("%d%d", &n, &m);
        verNum = n + 1;
        memset(maze, 0, sizeof(maze));
        for(int i = 0; i < verNum; i++){
            for(int j = i + 1; j < verNum; ++j){
                maze[i][j] = maze[j][i] = INF;
            }
        }
        for(int i = 0; i < m; ++i){
            int st, ed, dis;
            scanf("%d%d%d", &st, &ed, &dis);
            if(maze[st][ed] > dis){
                maze[st][ed] = maze[ed][st] = dis;
            }
        }
        Dijkstra(0);
        int p[verNum];
        for(int i = 1; i < verNum; ++i){
            scanf("%d", &p[i]);
        }
        int dp[1000001] = {0}, psum = 0, wt = 0;
        for(int i = 1; i < verNum; ++i){
            if(dist[i] != INF) wt += dist[i];
            psum += p[i];
        }
        for(int i = 1; i < verNum; ++i){
            if(dist[i] == INF) continue;
            for(int j = wt; j >= dist[i]; --j){
                dp[j] = max(dp[j], dp[j - dist[i]] + p[i]);
            }
        }
        bool flag = false;
        for(int i = 1; i <= wt; ++i){
            if(dp[i] * 2 > psum){
                printf("%d\n", i);
                flag = true;
                break;
            }
        }
        if(!flag){
            printf("impossible\n");
        }
    }
    return 0;
}
