#include <cstdio>
#include <cstring>

const int MAX = 100;
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
    int res = 0;
    memset(linker, -1, sizeof(linker));
    for(int u = 0; u < uN; ++u){
        memset(used, 0, sizeof(used));
        if(dfs(u)) ++res;
    }
    return res;
}

int main(){
    while(scanf("%d", &uN) == 1 && uN != 0){
        int k;
        scanf("%d%d", &vN, &k);
        memset(maze, 0, sizeof(maze));
        for(int i = 0; i < k; ++i){
            int t, x, y;
            scanf("%d%d%d", &t, &x, &y);
            if(x > 0 && y > 0) maze[x][y] = 1;
        }
        printf("%d\n", hungary());
    }
    return 0;
}
