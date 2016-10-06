#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct Point{
    int x, y;
};

struct Node{
    int x, y, step;
    Point pst;
    friend bool operator<(const Node &t1, const Node &t2){
        return t1.step > t2.step;
    }
};

const int MAX = 7;
int maze[MAX][MAX], N, M, dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
Node st, ed;
bool visTemp[MAX][MAX], vis[MAX][MAX], flag, mark[MAX][MAX][MAX][MAX];
Point ped;

void dfs(Point p){
    if(flag) return;
    if(p.x == ped.x && p.y == ped.y){
        flag = true;
        return;
    }
    Point next;
    for(int i = 0; i < 4 && !flag; ++i){
        next.x = p.x + dir[i][0];
        next.y = p.y + dir[i][1];
        if(next.x >= 0 && next.x < M && next.y >= 0 && next.y < N &&
            !visTemp[next.x][next.y]){
            visTemp[next.x][next.y] = true;
            dfs(next);
            visTemp[next.x][next.y] = false;
        }
    }
}

int bfs(){
    priority_queue<Node> que;
    que.push(st);
    while(!que.empty()){
        Node now = que.top();
        que.pop();
        if(now.x == ed.x && now.y == ed.y){
            return now.step;
        }
        if(mark[now.pst.x][now.pst.y][now.x][now.y]) continue;
        for(int i = 0; i < 4; ++i){
            Node next;
            next.x = now.x + dir[i][0];
            next.y = now.y + dir[i][1];
            ped.x = now.x - dir[i][0];
            ped.y = now.y - dir[i][1];
            if(next.x >= 0 && next.x < M && next.y >= 0 && next.y < N &&
                ped.x >= 0 && ped.x < M && ped.y >= 0 && ped.y < N &&
                maze[next.x][next.y] == 0 && maze[ped.x][ped.y] != 1){
                flag = false;
                memcpy(visTemp, vis, sizeof(vis));
                visTemp[now.pst.x][now.pst.y] = visTemp[now.x][now.y] = true;
                dfs(now.pst);
                if(flag){
                    next.step = now.step + 1;
                    next.pst.x = now.x, next.pst.y = now.y;
                    que.push(next);
                }
            }
        }
        mark[now.pst.x][now.pst.y][now.x][now.y] = true;
    }
    return -1;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d%d", &M, &N);
        for(int i = 0; i < M; ++i){
            for(int j = 0; j < N; ++j){
                scanf("%d", &maze[i][j]);
                if(maze[i][j] == 1){
                    vis[i][j] = true;
                }else{
                    if(maze[i][j] == 4){
                        st.pst.x = i, st.pst.y = j;
                    }else if(maze[i][j] == 2){
                        st.x = i, st.y = j, st.step = 0;
                    }else if(maze[i][j] == 3){
                        ed.x = i, ed.y = j;
                    }
                    maze[i][j] = 0;
                    vis[i][j] = false;
                }
            }
        }
        memset(mark, 0, sizeof(mark));
        printf("%d\n", bfs());
    }
    return 0;
}
