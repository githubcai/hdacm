#include <cstdio>
#include <cstring>

const int INF = 0x7fffff, MAX = 100;
int maze[MAX][MAX], dist[MAX], verNum;
bool used[MAX];

void Dijkstra(int v){
    memset(used, 0, sizeof(used));
    for(int i = 0; i < verNum; ++i){
        dist[i] = maze[v][i];
    }
    used[v] = true;
    for(int i = 1; i < verNum; ++i){
        int tMin = INF, mark = 0;
        for(int j = 0; j < verNum; ++j){
            if(dist[j] < tMin && !used[j]){
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

int main(){
    int M;
    while(scanf("%d%d", &verNum, &M) == 2 && !(verNum == 0 && M == 0)){
        memset(maze, 0, sizeof(maze));
        for(int i = 0; i < verNum; ++i){
            for(int j = i + 1; j < verNum; ++j){
                maze[i][j] = maze[j][i] = INF;
            }
        }
        for(int i = 0; i < M; ++i){
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            maze[a - 1][b - 1] = maze[b - 1][a - 1] = c;
        }
        Dijkstra(0);
        printf("%d\n", dist[verNum - 1]);
    }
    return 0;
}
