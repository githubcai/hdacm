#include <cstdio>
#include <cstring>

const int MAX = 1000;
int maze[MAX][MAX], uN, vN, linker[MAX];
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
    while(scanf("%d", &uN) == 1){
        vN = uN;
        memset(maze, 0, sizeof(maze));
        for(int i = 0; i < uN; ++i){
            int u, m;
            scanf("%d: (%d)", &u, &m);
            for(int j = 0; j < m; ++j){
                int v; scanf("%d", &v);
                maze[u][v] = 1;
            }
        }
        printf("%d\n", uN - hungary() / 2);
    }
    return 0;
}
