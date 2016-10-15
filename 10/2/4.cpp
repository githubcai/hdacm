#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 200;
bool maze[MAX][MAX], used[MAX];
int color[MAX], n, m;
int linker[MAX], uN, vN;

bool judge(int u){
    for(int i = 0; i < n; ++i){
        if(!maze[u][i]) continue;
        if(color[u] == color[i]) return false;
        if(color[i] == 0){
            color[i] = -color[u];
            if(!judge(i)) return false;
        }
    }
    return true;
}

bool dfs(int u){
    for(int v = 0; v < vN; ++v){
        if(maze[u][v] && !used[v]){
            used[v] = true;
            if(linker[v] == - 1 || dfs(linker[v])){
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
    while(scanf("%d%d", &n, &m) == 2){
        memset(maze, 0, sizeof(maze));
        for(int i = 0; i < m; ++i){
            int a, b; scanf("%d%d", &a, &b);
            maze[a - 1][b - 1] = maze[b - 1][a - 1] = true;
        }
        memset(color, 0, sizeof(color));
        color[0] = 1;
        if(judge(0)){
            uN = vN = n;
            printf("%d\n", hungary() / 2);
        }else{
            printf("No\n");
        }
    }
    return 0;
}
