#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

struct Node{
    int x, y, step;
};

const int MAX = 205;
char maze[MAX][MAX];
int n, m, dist[2][MAX][MAX], dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
Node st;
bool vis[MAX][MAX];

void bfs(int s){
    queue<Node> que;
    memset(vis, 0, sizeof(vis));
    memset(dist[s], -1, sizeof(dist[s]));
    vis[st.x][st.y] = true;
    dist[s][st.x][st.y] = 0;
    que.push(st);
    while(!que.empty()){
        Node now = que.front();
        que.pop();
        for(int i = 0; i < 4; ++i){
            Node next;
            next.x = now.x + dir[i][0];
            next.y = now.y + dir[i][1];
            if(!vis[next.x][next.y] && next.x >= 0 && next.x < n && next.y >= 0 && next.y < m && maze[next.x][next.y] != '#'){
                vis[next.x][next.y] = true;
                next.step = now.step + 1;
                dist[s][next.x][next.y] = next.step;
                que.push(next);
            }
        }
    }
}

int main(){
    while(scanf("%d%d", &n, &m) == 2){
        for(int i = 0; i < n; ++i){
            scanf("%s", maze[i]);
        }
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if(maze[i][j] == 'Y'){
                    st.x = i, st.y = j, st.step = 0;
                    bfs(0);
                }
                if(maze[i][j] == 'M'){
                    st.x = i, st.y = j, st.step = 0;
                    bfs(1);
                }
            }
        }
        int min = 999999999;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if(maze[i][j] == '@' && dist[0][i][j] != -1 && dist[1][i][j] != -1){
                    int temp = dist[0][i][j] + dist[1][i][j];
                    if(min > temp) min = temp;
                }
            }
        }
        printf("%d\n", min * 11);
    }
    return 0;
}
