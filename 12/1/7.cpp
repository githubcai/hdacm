#include <cstdio>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;

const int MAX = 801;
struct Node{
    int x, y;
};

char maze[MAX][MAX];
int n, m, step;
Node M, G, Z[2], now, nt;
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
queue<Node> que[2];
bool vis[2][MAX][MAX];

bool check(Node node){
    if(node.x < 0 || node.x >= n || node.y < 0 || node.y >= m) return false;
    if(maze[node.x][node.y] == 'X') return false;
    if(abs(node.x - Z[0].x) + abs(node.y - Z[0].y) <= 2 * step) return false;
    if(abs(node.x - Z[1].x) + abs(node.y - Z[1].y) <= 2 * step) return false;
    return true;
}

bool bfs(int w){
    int sum = que[w].size();
    while(sum-- > 0){
        now = que[w].front();
        que[w].pop();
        if(!check(now)) continue;
        for(int i = 0; i < 4; ++i){
            nt.x = now.x + dir[i][0];
            nt.y = now.y + dir[i][1];
            if(check(nt)){
                if(!vis[w][nt.x][nt.y]){
                    if(vis[w ^ 1][nt.x][nt.y]) return true;
                    vis[w][nt.x][nt.y] = true;
                    que[w].push(nt);
                }
            }
        }
    }
    return false;
}

int solve(){
    for(int i = 0; i < 2; ++i){
        while(!que[i].empty()) que[i].pop();
    }
    memset(vis, 0, sizeof(vis));
    now = M; que[0].push(now); vis[0][now.x][now.y] = true;
    now = G; que[1].push(now); vis[1][now.x][now.y] = true;
    step = 0;
    while(!que[0].empty() || !que[1].empty()){
        ++step;
        if(bfs(0)) return step;
        if(bfs(0)) return step;
        if(bfs(0)) return step;
        if(bfs(1)) return step;
    }
    return -1;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d%d", &n, &m);
        int cnt = 0;
        for(int i = 0; i < n; ++i){
            scanf("%s", maze[i]);
            for(int j = 0; j < m; ++j){
                if(maze[i][j] == 'Z'){
                    Z[cnt].x = i, Z[cnt].y = j;
                    ++cnt;
                }else if(maze[i][j] == 'M'){
                    M.x = i, M.y = j;
                }else if(maze[i][j] == 'G'){
                    G.x = i, G.y = j;
                }
            }
        }
        printf("%d\n", solve());
    }
    return 0;
}
