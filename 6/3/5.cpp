#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MAX = 100;
int uN, vN, maze[MAX][MAX], linker[MAX];
bool used[MAX];

bool dfs(int u, int color){
    for(int v = 0; v < vN; ++v){
        if(maze[u][v] == color && !used[v]){
            used[v] = true;
            if(linker[v] == -1 || dfs(linker[v], color)){
                linker[v] = u;
                return true;
            }
        }
    }
    return false;
}

int hungary(int color){
    int ret = 0;
    memset(linker, -1, sizeof(linker));
    for(int u = 0; u < uN; ++u){
        memset(used, 0, sizeof(used));
        if(dfs(u, color)) ++ret;
    }
    return ret;
}

int main(){
    int k;
    while(scanf("%d%d", &uN, &k) == 2 && !(uN == 0 && k == 0)){
        vN = uN;
        for(int i = 0; i < uN; ++i){
            for(int j = 0; j < vN; ++j){
                scanf("%d", &maze[i][j]);
            }
        }
        
        vector<int> store;
        for(int i = 1; i <= 50; ++i){
            if(k < hungary(i)) store.push_back(i);
        }
        if(store.size() == 0){
            printf("-1\n");
        }else{
            auto iter = store.begin();
            printf("%d", *iter);
            for(++iter; iter != store.end(); ++iter){
                printf(" %d", *iter);
            }
            printf("\n");
        }
    }
    return 0;
}
