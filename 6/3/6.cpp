#include <cstdio>
#include <cstring>

const int MAX = 26;
int maze[MAX][MAX], uN, vN, linker[MAX];
bool vis[MAX];

int trans(char *ch){
    int ret = 0;
    if(ch[0] >= '2' && ch[0] <= '9'){
        ret = (ch[0] - '2') * 4;
    }else{
        switch(ch[0]){
            case 'T': ret = 32; break;
            case 'J': ret = 36; break;
            case 'Q': ret = 40; break;
            case 'K': ret = 44; break;
            case 'A': ret = 48; break;
        }
    }
    switch(ch[1]){
        case 'C': break;
        case 'D': ret += 1; break;
        case 'S': ret += 2; break;
        case 'H': ret += 3; break;
    }
    return ret;
}

bool dfs(int u){
    for(int v = 0; v < vN; ++v){
        if(maze[u][v] && !vis[v]){
            vis[v] = true;
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
        memset(vis, 0, sizeof(vis));
        if(dfs(u)) ++ret;
    }
    return ret;
}

int main(){
    int N;
    scanf("%d", &N);
    while(N-- > 0){
        int k;
        scanf("%d", &k);
        int Adam[MAX], Eve[MAX];
        char ch[3];
        for(int i = 0; i < k; ++i){
            scanf("%s", ch);
            Adam[i] = trans(ch);
        }
        for(int i = 0; i < k; ++i){
            scanf("%s", ch);
            Eve[i] = trans(ch);
        }
        memset(maze, 0, sizeof(maze));
        uN = vN = k;
        for(int i = 0; i < k; ++i){
            for(int j = 0; j < k; ++j){
                if(Eve[j] > Adam[i]) maze[i][j] = 1;
            }
        }
        printf("%d\n", hungary());
    }
    return 0;
}
