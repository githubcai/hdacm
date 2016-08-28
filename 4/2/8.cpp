#include <cstdio>
#include <queue>
#include <cstring>
#include <cctype>
using namespace std;

struct Node{
    int x, y, num, time;
};

const int MAX = 101, CMAX = 28, INF = 999999999;
char maze[MAX][MAX];
int vis[MAX][MAX][CMAX], dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}, height, width, result;
Node st;

void bfs(){
    queue<Node> que;
    vis[st.x][st.y][st.num] = 0;
    que.push(st);
    while(!que.empty()){
        Node now = que.front();
        que.pop();
        if(now.time >= result) continue;
        if(maze[now.x][now.y] == '$'){
            result = now.time;
            continue;
        }
        for(int i = 0; i < 4; ++i){
            Node next;
            next.x = now.x + dir[i][0];
            next.y = now.y + dir[i][1];
            if(!isupper(maze[next.x][next.y]) && maze[next.x][next.y] != '#' && maze[next.x][next.y] != '*' &&
                next.x >= 0 && next.y >= 0 && next.x < height && next.y < width){
                if(isdigit(maze[next.x][next.y])){
                    if(now.num >= 1){
                        next.num = now.num - 1;
                        next.time = now.time;
                        if(next.time < vis[next.x][next.y][next.num] && next.time < result){
                            vis[next.x][next.y][next.num] = next.time;
                            que.push(next);
                        }
                    }
                    next.num = now.num;
                    next.time = now.time + maze[next.x][next.y] - '0';
                    if(next.time < vis[next.x][next.y][next.num] && next.time < result){
                        vis[next.x][next.y][next.num] = next.time;
                        que.push(next);
                    }
                }else{
                    next.num = now.num;
                    next.time = now.time;
                    if(next.time < vis[next.x][next.y][next.num] && next.time < result){
                        vis[next.x][next.y][next.num] = next.time;
                        que.push(next);
                    }
                }
            }
        }
    }
}

int main(){
    while(scanf("%s\n", maze[0]) != EOF && maze[0][0] != '-'){
        result = INF;
        for(height = 1; ; ++height){
            scanf("%c", &maze[height][0]);
            if(maze[height][0] == '\n') break;
            for(int i = 1; ; ++i){
                scanf("%c", &maze[height][i]);
                if('\n' == maze[height][i]) break;
            }
        }
        width = strlen(maze[0]);

        for(int l = 0; l < height; ++l){
            for(int n = 0; n < width; ++n){
                for(int m = 0; m < CMAX; ++m){
                    vis[l][n][m] = INF;
                }
            }
        }
        for(int i = 0; i < height; ++i){
            for(int j = 0; j < width; ++j){
                if(maze[i][j] == '#' || isupper(maze[i][j])){
                    st.x = i, st.y = j, st.time = 0;
                    st.num = (maze[i][j] == '#' ? 0 : maze[i][j] - '@');
                    bfs();
                }
            }
        }
        if(result == INF){
            printf("IMPOSSIBLE\n");
        }else{
            printf("%d\n", result);
        }
    }
    return 0;
}
