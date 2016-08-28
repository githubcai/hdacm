#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MAX = 1250;
int uN, vN, linker[MAX], muse[50][50];
bool used[MAX];
int dir[12][2] = {
    {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2},
    {1, 2}, {2, 1}, {2, -1}, {1, -2},
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}};
vector<int> maze[MAX];

bool dfs(int u){
    for(auto iter = maze[u].begin(); iter != maze[u].end(); ++iter){
        int v = *iter;
        if(!used[v]){
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

void init(){
    for(int i = 0; i < MAX; ++i){
        maze[i].clear();
    }
}

int main(){
    int R, C, cnt = 0;
    while(scanf("%d%d", &R, &C) == 2 && !(R == 0 && C == 0)){
        for(int i = 0; i < R; ++i){
            for(int j = 0; j < C; ++j){
                scanf("%d", &muse[i][j]);
            }
        }
        init();
        uN = (R * C + 1) / 2;
        for(int i = 0; i < R; ++i){
            for(int j = 0; j < C; ++j){
                if(muse[i][j] != -1){
                    for(int k = 0; k < 12; ++k){
                        if((muse[i][j] >> k) & 1){
                            int x = i + dir[k][0], y = j + dir[k][1];
                            if(x >= 0 && x < R && y >= 0 && y < C && muse[x][y] != -1){
                                if((i + j) % 2 == 0){
                                    maze[(i * C + j) / 2].push_back((x * C + y) / 2);
                                }else{
                                    maze[(x * C + y) / 2].push_back((i * C + j) / 2);
                                }
                            }
                        }
                    }
                }
            }
        }
        printf("%d. %d\n", ++cnt, hungary());
    }
    return 0;
}
