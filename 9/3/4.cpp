#include <cstdio>
#include <cstring>

struct Node{
    int x, y, step;
};

const int MAX = 625;
bool maze[MAX][MAX], vis[MAX][MAX];
int n, m, dir[4][2] = {{0, 1}, {-1, 0}, {1, 0}, {0, -1}}, count;
char dire[4] = {'E', 'N', 'S', 'W'};
Node lastResult;

void dfs(Node node, int move){
    int x = node.x, y = node.y, step = node.step;
    do{
        vis[x][y] = true;
        x += dir[move][0];
        y += dir[move][1];
        ++step;
    }while(x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && !maze[x][y]);
    
    x -= dir[move][0], y -= dir[move][1];
    Node next = {x, y, --step}, temp;
    int flag = 0, nextd[2];
    if(move == 0 || move == 3){
        nextd[0] = 1, nextd[1] = 2;
    }else{
        nextd[0] = 0, nextd[1] = 3;
    }
    for(int i = 0; i < 2; ++i){
        temp.x = next.x + dir[nextd[i]][0];
        temp.y = next.y + dir[nextd[i]][1];
        if(temp.x >= 0 && temp.x < m && temp.y >= 0 && temp.y < n && !vis[temp.x][temp.y] && !maze[temp.x][temp.y]){
            dfs(next, nextd[i]);
        }else{
            ++flag;
        }
    }
    
    if(flag == 2 && next.step > count){
        count = next.step;
    }
    while(x != node.x || y != node.y){
        vis[x][y] = false;
        x -= dir[move][0], y -= dir[move][1]; 
    }
}

int main(){
    int cnt = 0;
    while(scanf("%d%d", &m, &n) == 2 && (m + n) != 0){
        memset(maze, 0, sizeof(maze));
        int r; scanf("%d", &r);
        for(int i = 0; i < r; ++i){
            int x, y; scanf("%d%d", &x, &y);
            maze[x][y] = true;
        }
        count = 0;
        memset(vis, 0, sizeof(vis));
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(maze[i][j]) continue;
                Node start = {i, j, 1};
                vis[i][j] = true;
                for(int k = 0; k < 4; ++k){
                    int x = i + dir[k][0], y = j + dir[k][1];
                    int tempC = count;
                    if(x >= 0 && x < m && y >= 0 && y < n && !maze[x][y]){
                        dfs(start, k);
                        if(tempC != count){
                            lastResult.x = i, lastResult.y = j, lastResult.step = k;
                        }
                    }
                }
                vis[i][j] = false;
            }
        }
        printf("Case %d: %d %d %d %c\n", ++cnt, count, lastResult.x, lastResult.y, dire[lastResult.step]);
    }
    return 0;
}
