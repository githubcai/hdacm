#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 9, INF = 0x7ffffff;
struct Node{
    int x, y;
};
char maze[MAX][MAX], cdir[][6] = {"east", "north", "south", "west"};
int step, N, path[50], dist[MAX][MAX], dir[4][2] = {{0, 1}, {-1, 0}, {1, 0}, {0, -1}};

bool onEdge(int x, int y){
    if(x == 0 || x == N - 1 || y == 0 || y == N - 1) return true;
    return false;
}

void bfs(){
    queue<Node> que;
    Node now, nxt;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            dist[i][j] = INF;
            if(onEdge(i, j) && maze[i][j] == '0'){
                now.x = i, now.y = j;
                dist[i][j] = 0;
                que.push(now);
            }
        }
    }
    while(!que.empty()){
        now = que.front();
        que.pop();
        for(int i = 0; i < 4; ++i){
            nxt.x = now.x + dir[i][0];
            nxt.y = now.y + dir[i][1];
            if(nxt.x >= 0 && nxt.x < N && nxt.y >= 0 && nxt.y < N &&
                maze[nxt.x][nxt.y] == '0'){
                if(dist[nxt.x][nxt.y] > dist[now.x][now.y] + 1){
                    dist[nxt.x][nxt.y] = dist[now.x][now.y] + 1;
                    que.push(nxt);
                }
            }
        }
    }
}

int getH(char cm[MAX][MAX]){
    int ret = 0;
    for(int i = 1; i < N - 1; ++i){
        for(int j = 1; j < N - 1; ++j){
            if(cm[i][j] == '0'){
                ret = max(ret, dist[i][j]);
            }
        }
    }
    return ret;
}

bool dfs(char cm[MAX][MAX], int cnt){
    if(cnt + getH(cm) > step) return false;
    if(cnt == step) return true;
    char temp[MAX][MAX];
    for(int i = 0; i < 4; ++i){
        for(int x = 0; x < N; ++x){
            for(int y = 0; y < N; ++y){
                temp[x][y] = '1';
            }
        }
        for(int x = 1; x < N - 1; ++x){
            for(int y = 1; y < N - 1; ++y){
                if(cm[x][y] == '1') continue;
                int tx = x + dir[i][0], ty = y + dir[i][1];
                if(maze[tx][ty] == '1'){
                    temp[x][y] = '0';
                }else{
                    temp[tx][ty] = '0';
                }
            }
        }
        path[cnt] = i;
        if(dfs(temp, cnt + 1)) return true;
    }
    return false;
}

int main(){
    bool isFirst = true;
    while(scanf("%d", &N) != EOF){
        for(int i = 0; i < N; ++i){
            scanf("%s", maze[i]);
        }
        bfs();
        step = 0;
        while(!dfs(maze, 0)){
            ++step;
        }
        if(!isFirst){
            printf("\n");
        }else{
            isFirst = false;
        }
        for(int i = 0; i < step; ++i){
            printf("%s\n", cdir[path[i]]);
        }
    }
    return 0;
}
