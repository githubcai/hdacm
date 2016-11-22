#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

typedef long long LL;
const int INF = 0x7fffffff, MAX = 1000007;
int ctoi[128];
struct Node{
    char maze[6][4];
    LL zip(){
        LL res = 0;
        for(int i = 0; i < 6; ++i){
            for(int j = 0; j < 4; ++j){
                res *= 6;
                res += ctoi[maze[i][j]];
            }
        }
        return res;
    }
};

char cube[6][5], ref[128], pos[6];
int step;
LL vis[2][MAX];
int dir[6][12][2] = {
    {{3, 0}, {3, 1}, {3, 3}, {3, 2}, {0, 1}, {0, 3}, {4, 2}, {4, 0}, {5, 1}, {5, 3}, {2, 1}, {2, 3}},
    {{3, 1}, {3, 3}, {3, 2}, {3, 0}, {4, 2}, {4, 0}, {5, 1}, {5, 3}, {2, 1}, {2, 3}, {0, 1}, {0, 3}},
    {{2, 0}, {2, 1}, {2, 3}, {2, 2}, {0, 2}, {0, 3}, {3, 0}, {3, 2}, {5, 1}, {5, 0}, {1, 3}, {1, 1}},
    {{2, 1}, {2, 3}, {2, 2}, {2, 0}, {3, 0}, {3, 2}, {5, 1}, {5, 0}, {1, 3}, {1, 1}, {0, 2}, {0, 3}},
    {{0, 0}, {0, 1}, {0, 3}, {0, 2}, {1, 0}, {1, 1}, {4, 0}, {4, 1}, {3, 0}, {3, 1}, {2, 0}, {2, 1}},
    {{0, 1}, {0, 3}, {0, 2}, {0, 0}, {4, 0}, {4, 1}, {3, 0}, {3, 1}, {2, 0}, {2, 1}, {1, 0}, {1, 1}}
};
queue<Node> que[2];
Node now, nxt;
bool flag;

int getHash(LL sz, int x){
    int p = sz % MAX;
    while(true){
        if(vis[x][p] == -1) return p;
        if(vis[x][p] == sz) return p;
        ++p;
        if(p > MAX) p = 0;
    }
    return -1;
}

void bfs(int x){
    int size = que[x].size();
    while(size-- > 0){
        now = que[x].front();
        que[x].pop();
        for(int i = 0; i < 6; ++i){
            for(int j = 0; j < 6; ++j){
                for(int k = 0; k < 4; ++k){
                    nxt.maze[j][k] = now.maze[j][k];
                }
            }
            for(int j = 0; j < 12; ++j){
                nxt.maze[dir[i ^ 1][j][0]][dir[i ^ 1][j][1]] = now.maze[dir[i][j][0]][dir[i][j][1]];
            }
            LL sz = nxt.zip();
            int stat1 = getHash(sz, x);
            if(vis[x][stat1] != -1) continue;
            int stat2 = getHash(sz, x ^ 1);
            if(vis[x ^ 1][stat2] != -1){
                flag = true;
                return;
            }
            vis[x][stat1] = sz;
            que[x].push(nxt);
        }
    }
}

int dbfs(){
    for(int i = 0; i < 2; ++i){
        while(!que[i].empty()) que[i].pop();
    }
    memset(vis, -1, sizeof(vis));
    for(int i = 0; i < 6; ++i){
        for(int j = 0; j < 4; ++j){
             now.maze[i][j] = cube[i][j];
        }
    }
    LL sz = now.zip();
    int status = getHash(sz, 0);
    vis[0][status] = sz;
    que[0].push(now);
    for(int i = 0; i < 6; ++i){
        for(int j = 0; j < 4; ++j){
            now.maze[i][j] = pos[i];
        }
    }
    sz = now.zip();
    status = getHash(sz, 0);
    if(vis[0][status] != -1) return 0;
    status = getHash(sz, 1);
    vis[1][status] = sz;
    que[1].push(now);
    flag = false;
    int cnt = 0;
    while(true){
        ++cnt;
        if(que[0].size() < que[1].size()){
            bfs(0);
        }else{
            bfs(1);
        }
        if(flag) break;
    }
    return cnt;
}

int main(){
    ctoi['B'] = 0; ctoi['W'] = 1; ctoi['R'] = 2;
    ctoi['Y'] = 3; ctoi['O'] = 4; ctoi['G'] = 5;
    ref['B'] = 'G'; ref['W'] = 'Y'; ref['R'] = 'O';
    ref['Y'] = 'W'; ref['O'] = 'R'; ref['G'] = 'B';
    while(scanf("%s", cube[0]) != EOF){
        for(int i = 1; i < 4; ++i){
            scanf("%s", cube[0] + i);
        }
        for(int i = 1; i < 6; ++i){
            for(int j = 0; j < 4; ++j){
                scanf("%s", cube[i] + j);
            }
        }
        pos[0] = ref[cube[5][2]]; pos[1] = cube[1][2]; pos[2] = ref[cube[4][3]];
        pos[3] = ref[cube[1][2]]; pos[4] = cube[4][3]; pos[5] = cube[5][2];
        printf("%d\n", dbfs());
    }
    return 0;
}
