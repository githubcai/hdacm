#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct Node{
    int p[3], step;
};

const int MAX = 61;
char maze[MAX][MAX];
bool vis[MAX][MAX][MAX];
Node st;
int n;

void visit(int p1, int p2, int p3, int step, queue<Node> &que){
    vis[p1][p2][p3] = true;
    Node next;
    next.p[0] = p1;
    next.p[1] = p2;
    next.p[2] = p3;
    next.step = step + 1;
    que.push(next);
}

int bfs(){
    queue<Node> que;
    memset(vis, 0, sizeof(vis));
    st.step = 0;
    vis[st.p[0]][st.p[1]][st.p[2]] = true;
    que.push(st);
    while(!que.empty()){
        Node now = que.front();
        que.pop();
        if(now.p[0] == now.p[1] && now.p[1] == now.p[2]){
            return now.step;
        }
        for(int i = 1; i <= n; ++i){
            if(!vis[i][now.p[1]][now.p[2]] && maze[now.p[0]][i] == maze[now.p[1]][now.p[2]]){
                visit(i, now.p[1], now.p[2], now.step, que);
            }
        }
        for(int i = 1; i <= n; ++i){
            if(!vis[now.p[0]][i][now.p[2]] && maze[now.p[1]][i] == maze[now.p[0]][now.p[2]]){
                visit(now.p[0], i, now.p[2], now.step, que);
            }
        }
        for(int i = 1; i <= n; ++i){
            if(!vis[now.p[0]][now.p[1]][i] && maze[now.p[2]][i] == maze[now.p[1]][now.p[0]]){
                visit(now.p[0], now.p[1], i, now.step, que);
            }
        }
    }
    return -1;
}

int main(){
    while(scanf("%d", &n) == 1 && n != 0){
        scanf("%d%d%d", &st.p[0], &st.p[1], &st.p[2]);
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= n; ++j){
                scanf("%s", &maze[i][j]);
            }
        }
        int result = bfs();
        if(-1 == result){
            printf("impossible\n");
        }else{
            printf("%d\n", result);
        }
    }
    return 0;
}
