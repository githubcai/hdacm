#include <cstdio>
#include <cstring>

const int MAX = 100;
int uN, vN, maze[MAX][MAX], linker[MAX];;
bool used[MAX];

bool dfs(int u){
    for(int v = 0; v < vN; ++v){
        if(!used[v] && maze[u][v]){
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
    int K, cnt = 0;
    while(scanf("%d%d%d", &uN, &vN, &K) == 3){
        ++cnt;
        memset(maze, 0, sizeof(maze));
        for(int i = 0; i < K; ++i){
            int x, y;
            scanf("%d%d", &x, &y);
            maze[x - 1][y - 1] = 1;
        }
        int ret = hungary(), result = 0, temp[MAX];
        memcpy(temp, linker, sizeof(linker));
        for(int i = 0; i < vN; ++i){
            if(temp[i] == -1) continue;
            memcpy(linker, temp, sizeof(temp));
            linker[i] = -1;
            maze[temp[i]][i] = 0;
            memset(used, 0, sizeof(used));
            if(!dfs(temp[i])) ++result;
            maze[temp[i]][i] = 1;
        }
        printf("Board %d have %d important blanks for %d chessmen.\n", cnt, result, ret);
    }
    return 0;
}
