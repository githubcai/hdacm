#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int RMAX = 1000, CMAX = 1000;
char maze[RMAX][CMAX];
bool vis[RMAX][CMAX];
int sx, sy, ex, ey, r, c;
int dir[8][2] = {
    {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
    {1, 0}, {1, -1}, {0, -1}, {-1, -1}
};

struct Node{
    int x, y, time;
    friend bool operator<(const Node &a, const Node &b){
        return a.time > b.time;
    }
};

int bfs(){
    priority_queue<Node> que;
    Node next, now = {sx, sy, 0};
    memset(vis, 0, sizeof(vis));
    que.push(now);
    while(!que.empty()){
        now = que.top();
        que.pop();
        if(vis[now.x][now.y]) continue;
        vis[now.x][now.y] = true;
        if(now.x == ex && now.y == ey) return now.time;
        for(int i = 0; i < 8; ++i){
            next.x = now.x + dir[i][0];
            next.y = now.y + dir[i][1];
            next.time = now.time;
            if(!vis[next.x][next.y] && next.x >= 0 && next.x < r && next.y >= 0 && next.y < c){
                if(i != (maze[now.x][now.y] - '0')) ++next.time;
                que.push(next);
            }
        }
    }
    return -1;
}

int main(){
    while(scanf("%d%d", &r, &c) != EOF){
        for(int i = 0; i < r; ++i){
            scanf("%s", maze[i]);
        }
        int N; scanf("%d", &N);
        for(int i = 0; i < N; ++i){
            scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
            --sx, --sy, --ex, --ey;
            printf("%d\n", bfs());
        }
    }
    return 0;
}
