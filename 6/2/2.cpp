#include <cstdio>
#include <cstring>

const int INF = 0x7fffff, MAX = 1001;
int maze[MAX][MAX], dist[MAX], verNum;
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
        for(int j = 0; j < verNum; ++j){
            if(!used[j] && dist[j] > dist[mark] + maze[mark][j]){
                dist[j] = dist[mark] + maze[mark][j];
            }
        }
    }
}

int main(){
    int T, S, D;
    while(scanf("%d%d%d", &T, &S, &D) == 3){
        memset(maze, 0, sizeof(maze));
        verNum = -1;
        for(int i = 0; i < MAX; ++i){
            for(int j = i + 1; j < MAX; ++j){
                maze[i][j] = maze[j][i] = INF;
            }
        }
        for(int i = 0; i < T; ++i){
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            if(a > verNum) verNum = a;
            if(b > verNum) verNum = b;
            if(maze[a][b] > c) maze[a][b] = maze[b][a] = c;
        }
        for(int i = 0; i < S; ++i){
            int a;
            scanf("%d", &a);
            maze[0][a] = maze[a][0] = 0;
        }
        ++verNum;
        Dijkstra(0);
        int result = INF;
        for(int i = 0; i < D; ++i){
            int a;
            scanf("%d", &a);
            if(result > dist[a]) result = dist[a];
        }
        printf("%d\n", result);
    }
    return 0;
}
