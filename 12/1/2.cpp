#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef unsigned long long LL;
const int MAX = 8;
struct Node{
    int x, y, steps, num;
    LL bombs, walls;
    friend bool operator<(const Node &a, const Node &b){
        return a.steps > b.steps;
    }
};

char maze[MAX + 1][MAX + 1];
int N, M, numBomb, numWall, bomb[MAX][MAX], wall[MAX][MAX];
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int sx, sy, ex, ey;
vector<Node> vis[MAX][MAX][8 * 8 * 9 + 1];

bool check(const Node &now){
    vector<Node> temp = vis[now.x][now.y][now.num];
    for(int i = 0; i < temp.size(); ++i){
        if(now.bombs == temp[i].bombs && now.walls == temp[i].walls) return false;
    }
    return true;
}

int bfs(){
    priority_queue<Node> que;
    Node next, now = {sx, sy, 0, 0, 0, 0};
    vis[now.x][now.y][now.num].push_back(now);
    que.push(now);
    while(!que.empty()){
        now = que.top();
        que.pop();
        for(int i = 0; i < 4; ++i){
            next = now; ++next.steps;
            next.x = now.x + dir[i][0], next.y = now.y + dir[i][1];
            if(next.x >= 0 && next.x < N && next.y >= 0 && next.y < M){
                if(maze[next.x][next.y] == 'D'){
                    return next.steps;
                }else if(maze[next.x][next.y] == 'X' && ((1LL << wall[next.x][next.y]) & next.walls) == 0){
                    if(next.num > 0){
                        --next.num; ++next.steps;
                        next.walls |= (1LL << wall[next.x][next.y]);
                        vis[next.x][next.y][next.num].push_back(next);
                        que.push(next);
                    }
                }else if(maze[next.x][next.y] >= '1' && maze[next.x][next.y] <= '9' && ((1LL << bomb[next.x][next.y]) & next.bombs) == 0){
                    next.num += maze[next.x][next.y] - '0';
                    next.bombs |= (1LL << bomb[next.x][next.y]);
                    vis[next.x][next.y][next.num].push_back(next);
                    que.push(next);
                }else{
                    if(vis[next.x][next.y][next.num]. empty() ||check(next)){
                        vis[next.x][next.y][next.num].push_back(next);
                        que.push(next);
                    }
                }
            }
        }
    }
    return -1;
}

int main(){
    while(scanf("%d%d", &N, &M) != EOF && N + M){
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                for(int k = 0; k <= N * M * 9; ++k){
                    if(!vis[i][j][k].empty()) vis[i][j][k].clear();
                }
            }
        }
        numBomb = numWall = 0;
        for(int i = 0; i < N; ++i){
            scanf("%s", maze[i]);
            for(int j = 0; j < M; ++j){
                if(maze[i][j] == 'S'){
                    sx = i, sy = j;
                }else if(maze[i][j] == 'D'){
                    ex = i, ey = j;
                }else if(maze[i][j] == 'X'){
                    wall[i][j] = numWall++;
                }else if(maze[i][j] >= '1' && maze[i][j] <= '9'){
                    bomb[i][j] = numBomb++;
                }
            }
        }

        printf("%d\n", bfs());
    }
    return 0;
}
