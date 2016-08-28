#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct Node{
    int x, y, step;
};

Node st, ed;
bool vis[8][8];
int dir[8][2] = {
    {1, 2},
    {-1, 2},
    {1, -2},
    {-1, -2},
    {2, 1},
    {-2, 1},
    {2, -1},
    {-2, -1}
};

int bfs(){
    queue<Node> que;
    memset(vis, 0, sizeof(vis));
    st.step = 0;
    vis[st.x][st.y] = true;
    que.push(st);
    while(!que.empty()){
        Node now;
        now = que.front();
        que.pop();
        if(now.x == ed.x && now.y == ed.y){
            return now.step;
        }
        for(int i = 0; i < 8; ++i){
            Node next;
            next.x = now.x + dir[i][0];
            next.y = now.y + dir[i][1];
            if(next.x >= 0 && next.x < 8 &&
               next.y >= 0 && next.y < 8 &&
               !vis[next.x][next.y]){
                next.step = now.step + 1;
                que.push(next);
            }
        }
    }
    return -1;
}

int main(){
    char f[3], s[3];
    while(scanf("%s%s", f, s) != EOF){
        st.x = f[0] - 'a';
        st.y = f[1] - '1';
        ed.x = s[0] - 'a';
        ed.y = s[1] - '1';

        printf("To get from %s to %s takes %d knight moves.\n", f, s, bfs());
    }
    return 0;
}
