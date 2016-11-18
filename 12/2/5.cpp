#include <cstdio>
#include <queue>
using namespace std;

struct Node{
    char maze[20][21];
    int step, val, ans, num[20][20], x[50], y[50];
    friend bool operator<(const Node &a, const Node &b){
        return a.val < b.val;
    };
};

int n, m, dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}, cnt;
Node now, nx, ans;
bool vis[20][20];

void dfs(int x, int y, char c, char maze[20][21]){
    for(int i = 0; i < 4; ++i){
        int tx = x + dir[i][0], ty = y + dir[i][1];
        if(tx >= 0 && tx < n && ty >= 0 && ty < m && !vis[tx][ty] && maze[tx][ty] == c){
            vis[tx][ty] = true;
            ++cnt;
            dfs(tx, ty, c, maze);
        }
    }
}

void tran(int x, int y, char num, char (*maze)[21]){
    for(int i = 0; i < 4; ++i){
        int tx = x + dir[i][0], ty = y + dir[i][1];
        if(tx >= 0 && tx < n && ty >= 0 && ty < m && maze[tx][ty] == num){
            maze[tx][ty] = '0';
            tran(tx, ty, num, maze);
        }
    }
}

void move(char (*maze)[21]){
    for(int i = n - 1; i >= 0; --i){
        for(int j = 0; j < m; ++j){
            if(maze[i][j] == '0'){
                for(int k = i - 1; k >= 0; --k){
                    if(maze[k][j] > '0'){
                        maze[i][j] = maze[k][j];
                        maze[k][j] = '0';
                        break;
                    }
                }
            }
        }
    }
    int i, j;
    for(i = 0, j = 1; i < m - 1 && j < m;){
        if(maze[n - 1][i] > '0'){
            ++i;
            if(j <= i) j = i + 1;
            continue;
        }
        while(j < m){
            if(maze[n - 1][j] > '0'){
                for(int k = 0; k < n; ++k){
                    maze[k][i] = maze[k][j];
                    maze[k][j] = '0';
                }
                break;
            }
            ++j;
        }
    }
}

void eval(Node &node){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            vis[i][j] = false;
        }
    }
    node.val = node.ans;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            node.num[i][j] = 0;
            if(node.maze[i][j] > '0' && !vis[i][j]){
                vis[i][j] = true;
                cnt = 1;
                dfs(i, j, node.maze[i][j], node.maze);
                if(cnt > 1){
                    node.num[i][j] = cnt;
                    node.val += cnt * (cnt - 1);
                }
            }
        }
    }
}

int main(){
    while(scanf("%d%d", &n, &m) != EOF){
        priority_queue<Node> que;
        for(int i = 0; i < n; ++i){
            scanf("%s", now.maze[i]);
        }
        now.step = now.ans = now.val = 0;
        eval(now);
        que.push(now);
        int time = 0;
        ans.ans = 0;
        while(!que.empty()){
            now = que.top();
            if(now.ans > ans.ans) ans = now;
            ++time;
            if(time > 24) break;
            que.pop();
            for(int i = 0; i < n; ++i){
                for(int j = 0; j < m; ++j){
                    if(now.num[i][j]){
                        nx = now;
                        tran(i, j, nx.maze[i][j], nx.maze);
                        nx.maze[i][j] = '0';
                        move(nx.maze);
                        nx.x[nx.step] = i;
                        nx.y[nx.step] = j;
                        ++nx.step;
                        nx.ans += nx.num[i][j] * (nx.num[i][j] -1);
                        eval(nx);
                        que.push(nx);
                    }
                }
            }
        }
        printf("%d\n", ans.step);
        for(int i = 0; i < ans.step; ++i){
            printf("%d %d\n", ans.x[i], ans.y[i]);
        }
    }
    return 0;
}
