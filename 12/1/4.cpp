#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 60;
struct Mons{
    int x, y, d;
};

struct Node{
    int x, y, time;
};

char maze[MAX];
int n, m, mon, sx, sy, ex, ey;
int gh[MAX][MAX], ngh[MAX][MAX], trans[5] = {0, 2, 1, 4, 3};
Mons mons[MAX];
bool vis[MAX][MAX];
int dir[5][2] = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int mdir[4][9][2] = {
    {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}, {-2, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {-2, 2}},
    {{0, 0}, {1, -1}, {1, 0}, {1, 1}, {2, -2}, {2, -1}, {2, 0}, {2, 1}, {2, 2}},
    {{0, 0}, {-1, -1}, {0, -1}, {1, -1}, {-2, -2}, {-1, -2}, {0, -2}, {1, -2}, {2, -2}},
    {{0, 0}, {-1, 1}, {0, 1}, {1, 1}, {-2, 2}, {-1, 2}, {0, 2}, {1, 2}, {2, 2}}
};

void moveMons(){
    for(int i = 0; i < mon; ++i){
        int x = mons[i].x + dir[mons[i].d][0], y = mons[i].y + dir[mons[i].d][1];
        if(x >= 0 && x < n && y >= 0 && y < m && gh[x][y] == 0){
            mons[i].x = x, mons[i].y = y;
        }else{
            mons[i].d = trans[mons[i].d];
        }
    }
}

void makeGraph(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            ngh[i][j] = gh[i][j];
        }
    }
    for(int i = 0; i < mon; ++i){
        for(int j = 0; j < 9; ++j){
            int x = mons[i].x + mdir[mons[i].d - 1][j][0], y = mons[i].y + mdir[mons[i].d - 1][j][1];
            if(x >= 0 && x < n && y >= 0 && y < m && ngh[x][y] == 0) ngh[x][y] = 1;
        }
    }
}

int bfs(){
    queue<Node> que;
    int cur = -1;
    Node now, next;
    makeGraph();
    if(ngh[sx][sy] == 1) return -1;
    now.x = sx, now.y = sy, now.time = 0;
    que.push(now);
    while(!que.empty()){
        now = que.front();
        que.pop();
        if(now.time > 1000) break;
        if(now.x == ex && now.y == ey) return now.time;
        if(cur != now.time){
            for(int i = 0; i < n; ++i){
                for(int j = 0; j < m; ++j){
                    vis[i][j] = false;
                }
            }
            cur = now.time;
            moveMons();
            makeGraph();
        }
        for(int i = 0; i < 5; ++i){
            next.x = now.x + dir[i][0], next.y = now.y + dir[i][1];
            if(next.x >= 0 && next.x < n && next.y >= 0 && next.y < m && ngh[next.x][next.y] == 0 && !vis[next.x][next.y]){
                vis[next.x][next.y] = true;
                next.time = now.time + 1;
                que.push(next);
            }
        }
    }
    return -1;
}

int main(){
    int T, Case = 1; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i){
            scanf("%s", maze);
            for(int j = 0; j < m; ++j){
                if(maze[j] == '*'){
                    gh[i][j] = 1;
                }else{
                    gh[i][j] = 0;
                    if(maze[j] == 'A'){
                        sx = i, sy = j;
                    }else if(maze[j] == 'B'){
                        ex = i, ey = j;
                    }
                }
            }
        }
        scanf("%d", &mon);
        for(int i = 0; i < mon; ++i){
            scanf("%d%d%d", &mons[i].x, &mons[i].y, &mons[i].d);
            --mons[i].x, --mons[i].y;
        }
        printf("Case %d: ", Case++);
        int ret = bfs();
        if(ret == -1){
            printf("胜败兵家事不期 卷土重来是大侠\n");
        }else{
            printf("%d\n", ret);
        }
    }
    return 0;
}
