#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

class Node{
public:
    int x, y, time;
    friend bool operator<(const Node &a, const Node &b){
        return a.time > b.time;
    }
};

const int MAX = 205;

char map[MAX][MAX];
bool vis[MAX][MAX];
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}, N, M;

int bfs(int x, int y){
    priority_queue<Node> que;
    Node st, ed;
    memset(vis, 0, sizeof(vis));
    st.x = x;
    st.y = y;
    st.time = 0;
    vis[st.x][st.y] = true;
    que.push(st);
    while(!que.empty()){
        st = que.top();
        que.pop();
        if(map[st.x][st.y] == 'r'){
            return st.time;
        }
        for(int i = 0; i < 4; ++i){
            ed.x = st.x + dir[i][0];
            ed.y = st.y + dir[i][1];
            if(!vis[ed.x][ed.y] && ed.x >= 0 && ed.y >= 0 && ed.x < N && ed.y < M && map[ed.x][ed.y] != '#'){
                vis[ed.x][ed.y] = true;
                if(map[ed.x][ed.y] == 'x'){
                    ed.time = st.time + 2;
                }else{
                    ed.time = st.time + 1;
                }
                que.push(ed);
            }
        }
    }
    return -1;
}

int main(){
    while(scanf("%d%d", &N, &M) == 2){
        for(int i = 0; i < N; ++i){
            scanf("%s", map[i]);
        }
        int x, y;
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                if(map[i][j] == 'a'){
                    x = i;
                    y = j;
                    i = N;
                    break;
                }
            }
        }

        int ans = bfs(x, y);
        if(ans == -1){
            printf("Poor ANGEL has to stay in the prison all his life.\n");
        }else{
            printf("%d\n", ans);
        }
    }
    return 0;
}
