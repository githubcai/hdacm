#include <cstdio>
#include <cstring>

struct Node{
    int x, y;
};

const int MAX = 50, TMAX = 100;
int uN, vN, maze[MAX][MAX], linker[MAX];
bool used[MAX];

bool dfs(int u){
    for(int v = 0; v < vN; ++v){
        if(maze[u][v] && !used[v]){
            used[v] = true;
            if(linker[v] == -1 || dfs(linker[v])){
                linker[v] = u;
                return true;
            }
        }
    }
    return false;
}

int hungary(){
    int ret = 0;
    memset(linker, -1, sizeof(linker));
    for(int u = 0; u < uN; ++u){
        memset(used, 0, sizeof(used));
        if(dfs(u)) ++ret;
    }
    return ret;
}

int main(){
    int N, M;
    while(scanf("%d%d", &N, &M) == 2 && !(N == 0 && M == 0)){
        int K, ponds[TMAX][TMAX];
        scanf("%d", &K);
        memset(ponds, 0, sizeof(ponds));
        for(int i = 0; i < K; ++i){
            int X, Y;
            scanf("%d%d", &X, &Y);
            ponds[X - 1][Y - 1] = 1;
        }
        uN = vN = 0;
        memset(maze, 0, sizeof(maze));
        Node even[MAX], odd[MAX];
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                if(ponds[i][j] == 0){
                    if((i + j) % 2 == 0){
                        even[uN].x = i;
                        even[uN++].y = j;
                    }else{
                        odd[vN].x = i;
                        odd[vN++].y = j;
                    }
                }
            }
        }
        for(int i = 0; i < uN; ++i){
            for(int j = 0; j < vN; ++j){
                if((even[i].x == odd[j].x && even[i].y + 1 == odd[j].y) ||
                   (even[i].x == odd[j].x && even[i].y - 1 == odd[j].y) ||
                   (even[i].x + 1 == odd[j].x && even[i].y == odd[j].y) ||
                   (even[i].x - 1 == odd[j].x && even[i].y == odd[j].y)){
                    maze[i][j] = 1; 
                }
            }
        }
        printf("%d\n", hungary());
        for(int i = 0; i < vN; ++i){
            if(linker[i] == -1) continue;
            printf("(%d,%d)--(%d,%d)\n", odd[i].x + 1, odd[i].y + 1, even[linker[i]].x + 1, even[linker[i]].y + 1);
        }
        printf("\n");
    }
    return 0;
}
