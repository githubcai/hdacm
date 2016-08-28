#include <cstdio>
#include <cstring>

const int MAX = 1001, INF = 0x7fffff;
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
            if(dist[j] < tMin && !used[j]){
                tMin = dist[j];
                mark = j;
            }
        }
        used[mark] = true;
        for(int i = 0; i < verNum; ++i){
            if(!used[i] && dist[i] > dist[mark] + maze[mark][i]){
                dist[i] = dist[mark] + maze[mark][i];
            }
        }
    }
}

int main(){
    int m, s;
    while(scanf("%d%d%d", &verNum, &m, &s) == 3){
        ++verNum;
        memset(maze, 0, sizeof(maze));
        for(int i = 0; i < verNum; ++i){
            for(int j = i + 1; j < verNum; ++j){
                maze[i][j] = maze[j][i] = INF;
            }
        }
        for(int i = 0; i < m; ++i){
            int p, q, t;
            scanf("%d%d%d", &p, &q, &t);
            if(maze[p][q] > t) maze[p][q] = t;
        }
        int w;
        scanf("%d", &w);
        for(int i = 0; i < w; ++i){
            int a;
            scanf("%d", &a);
            maze[0][a] = maze[a][0] = 0;
        }
        Dijkstra(0);
        if(dist[s] == INF){
            printf("-1\n");
        }else{
            printf("%d\n", dist[s]);
        }
    }
    return 0;
}
