#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct Node{
    int x, y, step, keys;
};

const int MAX = 20;
char maze[MAX][MAX + 1];
bool vis[MAX][MAX][1 << 10];
int N, M, T, sx, sy, ex, ey, dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int bfs(){
    queue<Node> que;
    Node now;
    now.x = sx, now.y = sy, now.step = now.keys = 0;
    que.push(now);
    memset(vis, 0, sizeof(vis));
    vis[now.x][now.y][now.keys] = true;
    while(!que.empty()){
        now = que.front();
        que.pop();
        if(now.x == ex && now.y == ey){
            return now.step;
        }
        for(int i = 0; i < 4; ++i){
            Node next;
            next.x = now.x + dir[i][0];
            next.y = now.y + dir[i][1];
            next.step = now.step + 1;
            if(next.x >= 0 && next.x < N && next.y >= 0 && next.y < M &&
                maze[next.x][next.y] != '*' && next.step < T){
                if(maze[next.x][next.y] >= 'A' && maze[next.x][next.y] <= 'J'){
                    if(!vis[next.x][next.y][now.keys]){
                        vis[next.x][next.y][now.keys] = true;
                        if(((now.keys >> (maze[next.x][next.y] - 'A')) & 1) == 1 ){
                            next.keys = now.keys;
                            que.push(next);
                        }
                    }
                }else if(maze[next.x][next.y] >= 'a' && maze[next.x][next.y] <= 'j'){
                    next.keys = now.keys | (1 << (maze[next.x][next.y] - 'a'));
                    if(!vis[next.x][next.y][next.keys]){
                        vis[next.x][next.y][next.keys] = true;
                        que.push(next);
                    }
                }else{
                    if(!vis[next.x][next.y][now.keys]){
                        vis[next.x][next.y][now.keys] = true;
                        next.keys = now.keys;
                        que.push(next);
                    }
                }
            }
        }
    }
    return -1;
}

int main(){
    while(scanf("%d%d%d", &N, &M, &T) == 3){
        for(int i = 0; i < N; ++i){
            scanf("%s", maze[i]);
        }
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                if(maze[i][j] == '@'){
                    maze[i][j] = '.';
                    sx = i, sy = j;
                }else if(maze[i][j] == '^'){
                    maze[i][j] = '.';
                    ex = i, ey = j;
                }
            }
        }
        printf("%d\n", bfs());
    }
    return 0;
}
