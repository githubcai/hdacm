#include <cstdio>
#include <cstring>

const int MAX = 120;
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
    int T;
    scanf("%d", &T);
    while(T-- > 0){
        memset(maze, 0, sizeof(maze));
        int m; scanf("%d%d", &uN, &m);
        vN = uN;
        for(int i = 0; i < m; ++i){
            int s, e;
            scanf("%d%d", &s, &e);
            maze[s - 1][e - 1] = 1;
        }
        printf("%d\n", uN - hungary());
    }
    return 0;
}
